#include "LIB_units.hh"

#include "KER_crankshaft.hh"
#include "KER_differential_equation_euler_solver.hh"
#include "KER_physics_generic.hh"
#include "KER_piston.hh"
#include "KER_rod.hh"

#include <iomanip>
#include <iostream>

int main(void) {
	GenericPhysicsWorld world(new EulerDifferentialEquationSolver, NULL);

	Crankshaft *crankshaft = KER_crankshaft_new(&world, float2(0.0f, 0.0f), 3.5f, 45e-4f, {RodJournal{LIB_unit_angle(90.0f, revlab::units::degrees), LIB_unit_distance(43, revlab::units::millimiter)}});
	Piston *piston = KER_piston_new(&world, float2(0.0f, LIB_unit_distance(193, revlab::units::millimiter)), 0.42, LIB_unit_distance(0.0f, revlab::units::millimiter));
	Rod *rod = KER_rod_new(&world, piston, crankshaft, 0, 0.55f, 14e-4f, LIB_unit_distance(150, revlab::units::millimiter));

	while (true) {
		fprintf(stdout, "%-16s [ X: %.3f Y: %.3f dX: %.3f dY: %.3f ]\n", "piston", piston->position.x, piston->position.y, piston->velocity.x, piston->velocity.y);
		fprintf(stdout, "%-16s [ X: %.3f Y: %.3f dX: %.3f dY: %.3f ]\n", "rod", rod->position.x, rod->position.y, rod->velocity.x, rod->velocity.y);
		fprintf(stdout, "%-16s [ X: %.3f Y: %.3f dX: %.3f dY: %.3f ]\n", "crankshaft", crankshaft->position.x, crankshaft->position.y, crankshaft->velocity.x, crankshaft->velocity.y);

		world.process(world.delta_time);

		_sleep(100);
	}

	return 0;
}