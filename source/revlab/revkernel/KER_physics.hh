#pragma once

#include "LIB_utildefines.hh"

#include <vector>

struct Constraint;
struct ForceGenerator;
struct RigidBody;
struct PhysicsWorld;

/* -------------------------------------------------------------------- */
/** \name Physics Structure/Type
 * \{ */

enum class ePhysicsWorld_Flag;

struct PhysicsRigidBodyStore {
	RigidBody *body;

	ePhysicsWorld_Flag flag;
};

struct PhysicsConstraintStore {
	Constraint *constraint;

	ePhysicsWorld_Flag flag;
};

struct PhysicsForceGeneratorStore {
	ForceGenerator *force_generator;

	ePhysicsWorld_Flag flag;
}

enum class ePhysicsWorld_Flag : int {
	None = 0,
	/**
	 * This object is directly owned by the #PhysicsWorld and should be freed upon removal.
	 * \note Calling #PhysicsWorld::remove_* would return NULL and the object would be freed,
	 * to override this functionality you should call the #PhysiscWorld::detach_* function instead.
	 */
	Owned = 1 << 0,
};

ENUM_OPERATORS(ePhysicsWorld_Flag, ePhysicsWorld_Flag::Owned);

struct PhysicsWorld {
	PhysicsWorld();
	virtual ~PhysicsWorld();

	/**
	 * Process everything in this #PhysicsWorld and advance the time by #dt,
	 * this function may ignore processing the world completely if the accumulated time
	 * from last frame is not at least 1.0 / frames.
	 *
	 * \param dt The delta time to process this world with.
	 */
	void process(float dt);

	PhysicsRigidBodyStore *add_rigid_body(RigidBody *body, ePhysicsWorld_Flag flag = ePhysicsWorld_Flag::None);
	/**
	 * This function might return NULL if the specified body does not exist within this #PhysicsWorld or
	 * if the ePhysicsWorld_Flag::Owned was specified, in which case the #RigidBody is also freed.
	 */
	RigidBody *remove_rigid_body(const RigidBody *body);
	/** This function is similar to #PhysicsWorld::remove_rigid_body but ignores the ePhysicsWorld_Flag::Owned flag. */
	RigidBody *detach_rigid_body(const RigidBody *body);
	/** Returns non-zero in case the #RigidBody exists in the #PhysicsWorld */
	bool has_rigid_body(const RigidBody *body);

	PhysicsConstraintStore *add_constraint(Constraint *constraint, ePhysicsWorld_Flag flag = ePhysicsWorld_Flag::None);
	/**
	 * This function might return NULL if the specified constraint does not exist within this #PhysicsWorld or
	 * if the ePhysicsWorld_Flag::Owned was specified, in which case the #Constraint is also freed.
	 */
	Constraint *remove_constraint(const Constraint *constraint);
	/** This function is similar to #PhysicsWorld::remove_constraint but ignores the ePhysicsWorld_Flag::Owned flag. */
	Constraint *detach_constraint(const Constraint *constraint);
	/** Returns non-zero in case the #Constraint exists in the #PhysicsWorld */
	bool has_constraint(const Constraint *constraint);

	PhysicsForceGeneratorStore *add_force_generator(ForceGenerator *force_generator, ePhysicsWorld_Flag flag = ePhysicsWorld_Flag::None);
	/**
	 * This function might return NULL if the specified force generator does not exist within this #PhysicsWorld or
	 * if the ePhysicsWorld_Flag::Owned was specified, in which case the #ForceGenerator is also freed.
	 */
	ForceGenerator *remove_force_generator(const ForceGenerator *force_generator);
	/** This function is similar to #PhysicsWorld::remove_force_generator but ignores the ePhysicsWorld_Flag::Owned flag. */
	ForceGenerator *detach_force_generator(const ForceGenerator *force_generator);
	/** Returns non-zero in case the #ForceGenerator exists in the #PhysicsWorld */
	bool has_force_generator(const ForceGenerator *force_generator);

	std::vector<PhysicsRigidBodyStore> rigid_bodies;
	std::vector<PhysicsConstraintStore> constraints;
	std::vector<PhysicsForceGeneratorStore> force_generators;

	/**
	 * The current frame of the simulation, used to compute delta time.
	 */
	int frame;
	/**
	 * Accumulated time since the last frame was incremented (used by #process).
	 * This value is measured in (s) seconds.
	 */
	float accumulated;

	static constexpr float delta_time = 1.0f / 60.0f;
};

/** \} */
