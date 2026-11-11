#pragma once

#include <assert.h>

/* -------------------------------------------------------------------- */
/** \name Misc Macros
 * \{ */

/** Utility macro that wraps `std::enable_if` to make it a bit easier to use and less verbose in common cases. */
#define REVLAB_ENABLE_IF(condition) typename std::enable_if_t<(condition)> * = nullptr

/** \} */
