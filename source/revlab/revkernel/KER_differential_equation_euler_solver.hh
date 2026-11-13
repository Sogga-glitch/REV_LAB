#pragma once

#include "KER_differential_equation_solver.hh"

struct EulerDifferentialEquationSolver;

/* -------------------------------------------------------------------- */
/** \name Differential Equation Solver Structure/Type
 * \{ */

struct EulerDifferentialEquationSolver : public DifferentialEquationSolver {
	EulerDifferentialEquationSolver();
	virtual ~EulerDifferentialEquationSolver();

	void init(PhysicsWorld *world, float dt);
	/** Returns true if the loop should stop running (stop calling #solve). */
	bool step(PhysicsWorld *world);
	void solve(PhysicsWorld *world);
	void end();

	float dt;
};

/** \} */
