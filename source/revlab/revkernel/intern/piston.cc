#include "KER_piston.hh"

Piston::Piston(PhysicsWorld *world, const PistonDescr &descr) : RigidBody(descr.position, 0.0f, descr.mass, 1.0f), pin(descr.pin) {
	if (world) {
		world->add_rigid_body(this, ePhysicsWorld_Flag::Owned);
	}
}

Piston::~Piston() {
}

float2 Piston::wrist_pin_local() const {
	return float2(0.0f, pin);
}

/* -------------------------------------------------------------------- */
/** \name Piston Utilities
 * \{ */

Piston *KER_piston_new(PhysicsWorld *world, float2 position, float mass, float wrist_pin) {
	PistonDescr descr;

	descr.position = position;
	descr.mass = mass;
	descr.pin = wrist_pin;

	return new Piston(world, descr);
}

/** \} */
