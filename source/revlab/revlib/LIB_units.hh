#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

namespace revlab {

namespace units {

/* -------------------------------------------------------------------- */
/** \name Distance
 * \{ */

extern constexpr float kilometer = 1e+3f;
extern constexpr float meter = 1.0f;
extern constexpr float centimeter = 1e-2f;
extern constexpr float millimiter = 1e-3f;

extern constexpr float inch = centimeter * 2.54f;
extern constexpr float foot = inch * 12.0f;

extern constexpr float radians = 1.0f;
extern constexpr float degrees = 3.14159265358979323846f / 180.0f;

/** \} */

}  // namespace units

}  // namespace revlab

/** Convert a distance value into meters based on the input unit */
inline constexpr float LIB_unit_distance(float value, const float unit);
/** Convert a distance value into radians based on the input unit */
inline constexpr float LIB_unit_angle(float value, const float unit);

#include "intern/units_inline.cc"
