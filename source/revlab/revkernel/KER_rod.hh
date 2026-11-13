#pragma once

#include "KER_physics.hh"
#include "KER_rigid_body.hh"

struct Crankshaft;
struct Piston;
struct Rod;

/* -------------------------------------------------------------------- */
/** \name Rod Structure/Type
 * \{ */

struct RodDescr {
	Piston *piston;
	Crankshaft *crankshaft;
	size_t journal;

	float mass;
	float interia;
	float length;
};

struct Rod : public RigidBody {
	Rod(PhysicsWorld *world, const RodDescr &descriptor);
	virtual ~Rod();

	/**
	 * The "Big End" is the connection point of the rod to the crankshaft's journal.
	 */
	float2 big_end_local() const;
	/**
	 * The "Small End" is the connection point of the rod to the piston.
	 */
	float2 small_end_local() const;

	Piston *piston = nullptr;
	Crankshaft *crankshaft = nullptr;
	/** Each rod is connected to a journal with the crankshaft, this is the index of the journal in the crankshaft. */
	size_t journal;

	/** The total length of the rod. */
	float length;
};

/** \} */

/* -------------------------------------------------------------------- */
/** \name Rod Utilities
 * \{ */

/**
 * Function to quickly create a new rod for a specified piston.
 * \param world The physics world that governs this rod.
 * \param piston The piston this rod connects to the crankshaft.
 * \param crankshaft The crankshaft this rod connects to the piston.
 * \param journal The index of the journal in the crankshaft this rod connects to.
 * \param mass The mass of the rod.
 * \param inertia The moment of inertia of the rod.
 * \param length The length of the rod.
 * \return The newly created rod.
 */
Rod *KER_rod_new(PhysicsWorld *world, Piston *piston, Crankshaft *crankshaft, size_t journal, float mass, float inertia, float length);

/** \} */
