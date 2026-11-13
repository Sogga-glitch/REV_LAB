#pragma once

#include "LIB_units.hh"

struct Camshaft;

/* -------------------------------------------------------------------- */
/** \name Camshaft Structure/Type
 * \{ */

struct Camshaft {
	/**
	 * \brief The current displacement/advance of the camshaft around itself.
	 * This value is measured in (rad) radians.
	 */
	float theta = 0.0f;
	/**
	 * \brief The radius of the camshaft.
	 * This value is measured in (m) meters.
	 */
	float base_radius = LIB_unit_distance(15.0f, revlab::units::millimiter);

	Camshaft();
	Camshaft(float base_radius);
};

/** \} */
