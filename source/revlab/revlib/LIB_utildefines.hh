#pragma once

#include <assert.h>

/* -------------------------------------------------------------------- */
/** \name C++ Macros
 * \{ */

#ifdef __cplusplus

/* Useful to port C code using enums to C++ where enums are strongly typed.
 * To use after the enum declaration. */
/* If any enumerator `C` is set to say `A|B`, then `C` would be the max enum value. */
#	define ENUM_OPERATORS(_enum_type, _max_enum_value)                              \
		extern "C++" {                                                               \
		inline constexpr _enum_type operator|(_enum_type a, _enum_type b) {          \
			return (_enum_type)(uint64_t(a) | uint64_t(b));                          \
		}                                                                            \
		inline constexpr _enum_type operator&(_enum_type a, _enum_type b) {          \
			return (_enum_type)(uint64_t(a) & uint64_t(b));                          \
		}                                                                            \
		inline constexpr _enum_type operator~(_enum_type a) {                        \
			return (_enum_type)(~uint64_t(a) & (2 * uint64_t(_max_enum_value) - 1)); \
		}                                                                            \
		inline _enum_type &operator|=(_enum_type &a, _enum_type b) {                 \
			return a = (_enum_type)(uint64_t(a) | uint64_t(b));                      \
		}                                                                            \
		inline _enum_type &operator&=(_enum_type &a, _enum_type b) {                 \
			return a = (_enum_type)(uint64_t(a) & uint64_t(b));                      \
		}                                                                            \
		inline _enum_type &operator^=(_enum_type &a, _enum_type b) {                 \
			return a = (_enum_type)(uint64_t(a) ^ uint64_t(b));                      \
		}                                                                            \
		} /* extern "C++" */

#else
/* Output nothing. */
#	define ENUM_OPERATORS(_type, _max)
#endif

/** \} */

/* -------------------------------------------------------------------- */
/** \name Misc Macros
 * \{ */

/** Utility macro that wraps `std::enable_if` to make it a bit easier to use and less verbose in common cases. */
#define REVLAB_ENABLE_IF(condition) typename std::enable_if_t<(condition)> * = nullptr

/** \} */
