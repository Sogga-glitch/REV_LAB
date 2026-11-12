#pragma once

#include "LIB_units.hh"

inline constexpr float LIB_unit_distance(float value, const float unit) {
	return value * unit;
}
