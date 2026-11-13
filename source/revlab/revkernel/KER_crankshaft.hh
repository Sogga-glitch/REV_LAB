#pragma once

#include "LIB_math_vector_types.hh"

#include "KER_physics.hh"
#include "KER_rigid_body.hh"

struct Crankshaft;

/* -------------------------------------------------------------------- */
/** \name Crankshaft Structure/Type
 * \{ */

/**
 * We consider rod journals to be part of the crankshaft, they don't have a separate RidigBody, instead they act on the Crankshaft.
 * Each rod journal is identified by its angle and throw radius around the crankshaft.
 * \note throw is an identifier in C++ so we use radius instead.
 */
struct RodJournal {
	float theta;
	float radius;
};

struct CrankshaftDescr {
	float2 position;
	float mass;
	float intertia;
	std::vector<RodJournal> journals;
};

struct Crankshaft : public RigidBody {
	Crankshaft(PhysicsWorld *world, const CrankshaftDescr &descr);
	virtual ~Crankshaft();

	/**
	 * We only return the local position of the journal, since they are "bolted" on the crankshaft and they do not move.
	 * \note For rendering we need to multiple using the #RigidBody matrix.
	 */
	float2 journal_local(const RodJournal &descr) const;
	/**
	 * We only return the local position of the journal, since they are "bolted" on the crankshaft and they do not move.
	 * \note For rendering we need to multiple using the #RigidBody matrix.
	 */
	float2 journal_local(const size_t index) const;

	std::vector<RodJournal> journals;
};

/** \} */

/* -------------------------------------------------------------------- */
/** \name Crankshaft Utilities
 * \{ */

/**
 * Function to quickly create a new crankshaft.
 * \param world The physics world that governs this crankshaft.
 * \param position The position of the crankshaft in the world.
 * \param mass The mass of the crankshaft.
 * \param inertia The moment of inertia of the crankshaft.
 * \param journals The array of journals that this crankshaft has.
 * \return The newly created crankshaft.
 */
Crankshaft *KER_crankshaft_new(PhysicsWorld *world, float2 position, float mass, float inertia, const std::vector<RodJournal> &journals);

/** \} */
