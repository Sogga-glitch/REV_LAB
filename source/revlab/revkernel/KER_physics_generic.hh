#pragma once

#include "KER_differential_equation_solver.hh"
#include "KER_linear_equation_solver.hh"
#include "KER_physics.hh"

/* -------------------------------------------------------------------- */
/** \name Generic PhysicsWorld Structure/Type
 * \{ */

struct GenericPhysicsWorld : public PhysicsWorld {
	GenericPhysicsWorld(DifferentialEquationSolver *de_solver, LinearEquationSolver *le_solver);
	virtual ~GenericPhysicsWorld();

	virtual void update(float dt);

	DifferentialEquationSolver *differential_equation_solver;
	LinearEquationSolver *linear_equation_solver;
};

/** \} */
