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

}  // namespace revlab::math
