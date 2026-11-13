#include "KER_linear_equation_solver.hh"

LinearEquationSolver::LinearEquationSolver(bool supports_limits) : supports_limits(supports_limits) {
}

LinearEquationSolver::~LinearEquationSolver() {
}

bool LinearEquationSolver::solve() {
	return false;
}

bool LinearEquationSolver::solve_with_limits() {
	return false;
}
