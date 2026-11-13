#pragma once

#include "KER_physics.hh"

struct DifferentialEquationSolver;

/* -------------------------------------------------------------------- */
/** \name Differential Equation Solver Structure/Type
 * \{ */

struct DifferentialEquationSolver {
	DifferentialEquationSolver();
	virtual ~DifferentialEquationSolver();

	virtual void init(PhysicsWorld *world, float dt) = 0;
	/** Returns true if the loop should stop running (stop calling #solve). */
	virtual bool step(PhysicsWorld *world) = 0;
	virtual void solve(PhysicsWorld *world) = 0;
	virtual void end() = 0;
};

/** \} */
