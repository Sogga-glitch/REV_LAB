#include "KER_differential_equation_euler_solver.hh"
#include "KER_rigid_body.hh"

EulerDifferentialEquationSolver::EulerDifferentialEquationSolver() {
}
EulerDifferentialEquationSolver::~EulerDifferentialEquationSolver() {
}

void EulerDifferentialEquationSolver::init(PhysicsWorld *world, float dt) {
	this->dt = dt;
}

bool EulerDifferentialEquationSolver::step(PhysicsWorld *world) {
	return true;
}

void EulerDifferentialEquationSolver::solve(PhysicsWorld *world) {
	for (std::vector<PhysicsRigidBodyStore>::iterator itr = world->rigid_bodies.begin(); itr != world->rigid_bodies.end(); itr++) {
		PhysicsRigidBodyStore &store = *itr;
		RigidBody *erb = store.shallow_copy;
		const float inv_M = erb->mass > 0.0f ? 1.0f / erb->mass : 0.0f;
		const float inv_I = erb->inertia > 0.0f ? 1.0f / erb->inertia : 0.0f;

		erb->velocity += store.force * (inv_M * dt);
		erb->v_theta += store.torque * (inv_I * dt);

		erb->position += erb->velocity * dt;
		erb->theta += erb->v_theta * dt;
	}
}

void EulerDifferentialEquationSolver::end() {
}
