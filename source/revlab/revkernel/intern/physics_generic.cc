#include "KER_constraint.hh"
#include "KER_force_generator.hh"
#include "KER_physics_generic.hh"
#include "KER_rigid_body.hh"

using namespace revlab::math;

struct ConstraintRow {
	PhysicsRigidBodyStore *store[ConstraintMatrices::max_constraint_body_count];
	float3 J[ConstraintMatrices::max_constraint_body_count];
	float3 invM[ConstraintMatrices::max_constraint_body_count];
	size_t bodies;
};

GenericPhysicsWorld::GenericPhysicsWorld(DifferentialEquationSolver *de_solver, LinearEquationSolver *le_solver) {
	this->differential_equation_solver = de_solver;
	this->linear_equation_solver = le_solver;
}

GenericPhysicsWorld::~GenericPhysicsWorld() {
}

/* Dense Gaussian elimination with partial pivoting; solves A x = b in place (x returned in b). */
static bool solve_dense(std::vector<std::vector<float>> &A, std::vector<float> &b) {
	const size_t n = b.size();
	for (size_t col = 0; col < n; col++) {
		size_t pivot = col;
		for (size_t r = col + 1; r < n; r++) {
			if (fabsf(A[r][col]) > fabsf(A[pivot][col]))
				pivot = r;
		}
		if (fabsf(A[pivot][col]) < 1e-12f)
			return false; /* singular */
		std::swap(A[pivot], A[col]);
		std::swap(b[pivot], b[col]);

		for (size_t r = col + 1; r < n; r++) {
			const float f = A[r][col] / A[col][col];
			if (f == 0.0f)
				continue;
			for (size_t c = col; c < n; c++)
				A[r][c] -= f * A[col][c];
			b[r] -= f * b[col];
		}
	}
	for (size_t i = n; i-- > 0;) {
		float sum = b[i];
		for (size_t c = i + 1; c < n; c++)
			sum -= A[i][c] * b[c];
		b[i] = sum / A[i][i];
	}
	return true;
}

void GenericPhysicsWorld::update(float dt) {
	differential_equation_solver->init(this, dt);

	do {
		prepare();

		// process forces
		for (std::vector<PhysicsForceGeneratorStore>::iterator itr = force_generators.begin(); itr != force_generators.end(); itr++) {
			ForceGenerator *fg = itr->force_generator;
			fg->apply(this, dt);
		}

		// process constraints
		size_t total_constraints = 0;
		for (std::vector<PhysicsConstraintStore>::iterator itr = constraints.begin(); itr != constraints.end(); itr++) {
			Constraint *c = itr->constraint;

			/** How many of these constraints are actualy used, maximum is 3 since we may have constraints on all 3 values (x, y, \theta). */
			total_constraints += c->constraints;
		}

		std::vector<std::vector<float>> A(total_constraints, std::vector<float>(total_constraints, 0.0f));
		std::vector<float> b(total_constraints, 0.0f);
		std::vector<ConstraintRow> rows(total_constraints);

		size_t index = 0;

		ConstraintMatrices output;
		for (std::vector<PhysicsConstraintStore>::iterator itr = constraints.begin(); itr != constraints.end(); itr++) {
			Constraint *c = itr->constraint;

			KER_constraint_output_none(&output);
			c->apply(this, dt, &output);

			for (size_t subconstraint = 0; subconstraint < c->constraints; subconstraint++, index++) {
				ConstraintRow &row = rows[index];
				row.bodies = c->bodies;

				float rhs = 0.0f;
				for (size_t subbody = 0; subbody < c->bodies; subbody++) {
					RigidBody *rb = c->body[subbody];
					PhysicsRigidBodyStore *store = get_rigid_body_store(rb);

					assert(store);

					float3 v(rb->velocity, rb->v_theta);
					float3 Jr = output.J[subbody][subconstraint];
					float3 dJr = output.dJ[subbody][subconstraint];
					float3 Fext = float3(store->force, store->torque);
					float3 invM = float3(1.0f / rb->mass, 1.0f / rb->mass, 1.0f / rb->inertia);

					row.store[subbody] = store;
					row.J[subbody] = Jr;
					row.invM[subbody] = invM;

					rhs -= dot(dJr, v) + output.damping[subconstraint] * dot(Jr, v) + dot(Jr * invM, Fext);
				}
				rhs -= output.stiffness[subconstraint] * output.C[subconstraint];
				b[index] = rhs;
			}
		}

		/* A = J M^-1 J^T */
		for (size_t row = 0; row < total_constraints; row++) {
			for (size_t col = row; col < total_constraints; col++) {
				float sum = 0.0f;
				for (size_t k = 0; k < rows[row].bodies; k++) {
					for (size_t l = 0; l < rows[col].bodies; l++) {
						if (rows[row].store[k] == rows[col].store[l]) {
							sum += dot(rows[row].J[k] * rows[row].invM[k], rows[col].J[l]);
						}
					}
				}
				A[row][col] = sum;
				A[col][row] = sum;
			}
			A[row][row] += 1e-6f;
		}

		if (!solve_dense(A, b)) {
			break;
		}

		for (size_t constraint = 0; constraint < total_constraints; constraint++) {
			for (size_t subbody = 0; subbody < rows[constraint].bodies; subbody++) {
				PhysicsRigidBodyStore *store = rows[constraint].store[subbody];
				const float3 o = rows[constraint].J[subbody] * b[constraint];
				store->force.x += o.x;
				store->force.y += o.y;
				store->torque += o.z;
			}
		}

		differential_equation_solver->solve(this);
	} while (!differential_equation_solver->step(this));

	differential_equation_solver->end();

	for (std::vector<PhysicsRigidBodyStore>::iterator itr = rigid_bodies.begin(); itr != rigid_bodies.end(); itr++) {
		RigidBody *rb = itr->body;
		RigidBody *erb = itr->shallow_copy;

		rb->position = erb->position;
		rb->velocity = erb->velocity;

		rb->theta = erb->theta;
		rb->v_theta = erb->v_theta;
	}
}
