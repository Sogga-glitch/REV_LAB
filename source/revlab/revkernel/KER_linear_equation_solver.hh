#pragma once

struct LinearEquationSolver;

/* -------------------------------------------------------------------- */
/** \name Linear Equation Solver Structure/Type
 * \{ */

struct LinearEquationSolver {
	LinearEquationSolver(bool supports_limits);
	virtual ~LinearEquationSolver();

	virtual bool solve();
	virtual bool solve_with_limits();

	bool supports_limits;
};

/** \} */
