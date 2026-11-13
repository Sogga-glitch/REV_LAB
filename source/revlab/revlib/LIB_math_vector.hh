#pragma once

#include "LIB_math_vector_types.hh"

namespace revlab::math {

template<typename T, int Size> [[nodiscard]] inline VecBase<T, Size> abs(const VecBase<T, Size> &a) {
	VecBase<T, Size> result;
	for (int i = 0; i < Size; i++) {
		result[i] = a[i] >= 0 ? a[i] : -a[i];
	}
	return result;
}

/**
 * Dot product between two vectors.
 * Equivalent to component wise multiplication followed by summation of the result.
 * Equivalent to the cosine of the angle between the two vectors if the vectors are normalized.
 * \note prefer using `length_manhattan(a)` than `dot(a, vec(1))` to get the sum of all components.
 */
template<typename T, int Size> [[nodiscard]] inline T dot(const VecBase<T, Size> &a, const VecBase<T, Size> &b) {
	T result = a[0] * b[0];
	for (int i = 1; i < Size; i++) {
		result += a[i] * b[i];
	}
	return result;
}

}  // namespace revlab::math
