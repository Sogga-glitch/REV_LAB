#include "KER_constraint.hh"

Constraint::Constraint(size_t bodies, size_t constraints) : bodies(bodies), constraints(constraints) {
	for (size_t index = 0; index < sizeof(this->body) / sizeof(this->body[0]); index++) {
		this->body[index] = nullptr;
	}
}

Constraint::~Constraint() {
}

/* -------------------------------------------------------------------- */
/** \name Constraint Common Utilities
 * \{ */

void KER_constraint_output_none(ConstraintMatrices *r_output) {
	for (size_t index = 0; index < sizeof(r_output->J) / sizeof(r_output->J[0]); index++) {
		r_output->J[index] = float3x3::zero();
	}
	for (size_t index = 0; index < sizeof(r_output->dJ) / sizeof(r_output->dJ[0]); index++) {
		r_output->dJ[index] = float3x3::zero();
	}
	r_output->C = float3(0.0f);
	r_output->stiffness = float3(0.0f);
	r_output->damping = float3(0.0f);

	KER_constraint_output_no_limits(r_output);
}

void KER_constraint_output_no_limits(ConstraintMatrices *r_output) {
	r_output->min = float3(-FLT_MAX);
	r_output->max = float3(+FLT_MAX);
}

/** \} */
