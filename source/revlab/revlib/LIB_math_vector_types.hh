#pragma once

#include "LIB_unroll.hh"
#include "LIB_utildefines.hh"

#include <array>
#include <cmath>
#include <type_traits>

namespace revlab {

/* clang-format off */
template<typename T>
using as_uint_type = std::conditional_t<sizeof(T) == sizeof(uint8_t), uint8_t,
                     std::conditional_t<sizeof(T) == sizeof(uint16_t), uint16_t,
                     std::conditional_t<sizeof(T) == sizeof(uint32_t), uint32_t,
                     std::conditional_t<sizeof(T) == sizeof(uint64_t), uint64_t, void>>>>;
/* clang-format on */

template<typename T, int Size> struct vec_struct_base {
	std::array<T, Size> values;
};

template<typename T> struct vec_struct_base<T, 2> {
	T x, y;
};

template<typename T> struct vec_struct_base<T, 3> {
	T x, y, z;
};

template<typename T> struct vec_struct_base<T, 4> {
	T x, y, z, w;
};

template<typename T, int Size> struct VecBase : public vec_struct_base<T, Size> {
#define REVLAB_ENABLE_IF_VEC(_size, _test) int S = _size, REVLAB_ENABLE_IF((S _test))

	static_assert(alignof(T) <= sizeof(T), "VecBase is not compatible with aligned type for now.");

	static constexpr int type_length = Size;

	using base_type = T;
	using uint_type = VecBase<as_uint_type<T>, Size>;

	VecBase() = default;

	template<REVLAB_ENABLE_IF_VEC(Size, > 1)> explicit VecBase(T value) {
		for (int i = 0; i < Size; i++) {
			(*this)[i] = value;
		}
	}

	template<typename U, REVLAB_ENABLE_IF((std::is_convertible_v<U, T>))> explicit VecBase(U value) : VecBase(T(value)) {
	}

	template<REVLAB_ENABLE_IF_VEC(Size, == 1)> VecBase(T _x) {
		(*this)[0] = _x;
	}

	template<REVLAB_ENABLE_IF_VEC(Size, == 2)> VecBase(T _x, T _y) {
		(*this)[0] = _x;
		(*this)[1] = _y;
	}

	template<REVLAB_ENABLE_IF_VEC(Size, == 3)> VecBase(T _x, T _y, T _z) {
		(*this)[0] = _x;
		(*this)[1] = _y;
		(*this)[2] = _z;
	}

	template<REVLAB_ENABLE_IF_VEC(Size, == 4)> VecBase(T _x, T _y, T _z, T _w) {
		(*this)[0] = _x;
		(*this)[1] = _y;
		(*this)[2] = _z;
		(*this)[3] = _w;
	}

	/** Mixed scalar-vector constructors. */

	template<typename U, REVLAB_ENABLE_IF_VEC(Size, == 3)> constexpr VecBase(const VecBase<U, 2> &xy, T z) : VecBase(T(xy.x), T(xy.y), z) {
	}

	template<typename U, REVLAB_ENABLE_IF_VEC(Size, == 3)> constexpr VecBase(T x, const VecBase<U, 2> &yz) : VecBase(x, T(yz.x), T(yz.y)) {
	}

	template<typename U, REVLAB_ENABLE_IF_VEC(Size, == 4)> VecBase(VecBase<U, 3> xyz, T w) : VecBase(T(xyz.x), T(xyz.y), T(xyz.z), T(w)) {
	}

	template<typename U, REVLAB_ENABLE_IF_VEC(Size, == 4)> VecBase(T x, VecBase<U, 3> yzw) : VecBase(T(x), T(yzw.x), T(yzw.y), T(yzw.z)) {
	}

	template<typename U, typename V, REVLAB_ENABLE_IF_VEC(Size, == 4)> VecBase(VecBase<U, 2> xy, VecBase<V, 2> zw) : VecBase(T(xy.x), T(xy.y), T(zw.x), T(zw.y)) {
	}

	template<typename U, REVLAB_ENABLE_IF_VEC(Size, == 4)> VecBase(VecBase<U, 2> xy, T z, T w) : VecBase(T(xy.x), T(xy.y), T(z), T(w)) {
	}

	template<typename U, REVLAB_ENABLE_IF_VEC(Size, == 4)> VecBase(T x, VecBase<U, 2> yz, T w) : VecBase(T(x), T(yz.x), T(yz.y), T(w)) {
	}

	template<typename U, REVLAB_ENABLE_IF_VEC(Size, == 4)> VecBase(T x, T y, VecBase<U, 2> zw) : VecBase(T(x), T(y), T(zw.x), T(zw.y)) {
	}

	/** Masking. */

	template<typename U, int OtherSize, REVLAB_ENABLE_IF(OtherSize > Size)> explicit VecBase(const VecBase<U, OtherSize> &other) {
		for (int i = 0; i < Size; i++) {
			(*this)[i] = T(other[i]);
		}
	}

#undef ROSE_ENABLE_IF_VEC

	/** Conversion from pointers (from C-style vectors). */

	VecBase(const T *ptr) {
		for (int i = 0; i < Size; i++) {
			(*this)[i] = ptr[i];
		}
	}

	template<typename U, REVLAB_ENABLE_IF((std::is_convertible_v<U, T>))> explicit VecBase(const U *ptr) {
		for (int i = 0; i < Size; i++) {
			(*this)[i] = ptr[i];
		}
	}

	VecBase(const T (*ptr)[Size]) : VecBase(static_cast<const T *>(ptr[0])) {
	}

	/** Conversion from other vector types. */

	template<typename U> explicit VecBase(const VecBase<U, Size> &vec) {
		for (int i = 0; i < Size; i++) {
			(*this)[i] = T(vec[i]);
		}
	}

	/** C-style pointer dereference. */

	operator const T *() const {
		return reinterpret_cast<const T *>(this);
	}

	operator T *() {
		return reinterpret_cast<T *>(this);
	}

	/** Array access. */

	const T &operator[](int index) const {
		assert(index >= 0);
		assert(index < Size);
		return reinterpret_cast<const T *>(this)[index];
	}

	T &operator[](int index) {
		assert(index >= 0);
		assert(index < Size);
		return reinterpret_cast<T *>(this)[index];
	}

	/** Arithmetic operators. */

	friend VecBase operator+(const VecBase &a, const VecBase &b) {
		VecBase result;
		unroll<Size>([&](auto i) { result[i] = a[i] + b[i]; });
		return result;
	}

	friend VecBase operator+(const VecBase &a, const T &b) {
		VecBase result;
		unroll<Size>([&](auto i) { result[i] = a[i] + b; });
		return result;
	}

	friend VecBase operator+(const T &a, const VecBase &b) {
		return b + a;
	}

	VecBase &operator+=(const VecBase &b) {
		unroll<Size>([&](auto i) { (*this)[i] += b[i]; });
		return *this;
	}

	VecBase &operator+=(const T &b) {
		unroll<Size>([&](auto i) { (*this)[i] += b; });
		return *this;
	}

	friend VecBase operator-(const VecBase &a) {
		VecBase result;
		unroll<Size>([&](auto i) { result[i] = -a[i]; });
		return result;
	}

	friend VecBase operator-(const VecBase &a, const VecBase &b) {
		VecBase result;
		unroll<Size>([&](auto i) { result[i] = a[i] - b[i]; });
		return result;
	}

	friend VecBase operator-(const VecBase &a, const T &b) {
		VecBase result;
		unroll<Size>([&](auto i) { result[i] = a[i] - b; });
		return result;
	}

	friend VecBase operator-(const T &a, const VecBase &b) {
		VecBase result;
		unroll<Size>([&](auto i) { result[i] = a - b[i]; });
		return result;
	}

	VecBase &operator-=(const VecBase &b) {
		unroll<Size>([&](auto i) { (*this)[i] -= b[i]; });
		return *this;
	}

	VecBase &operator-=(const T &b) {
		unroll<Size>([&](auto i) { (*this)[i] -= b; });
		return *this;
	}

	friend VecBase operator*(const VecBase &a, const VecBase &b) {
		VecBase result;
		unroll<Size>([&](auto i) { result[i] = a[i] * b[i]; });
		return result;
	}

	template<typename FactorT> friend VecBase operator*(const VecBase &a, FactorT b) {
		VecBase result;
		unroll<Size>([&](auto i) { result[i] = a[i] * b; });
		return result;
	}

	friend VecBase operator*(T a, const VecBase &b) {
		return b * a;
	}

	VecBase &operator*=(T b) {
		unroll<Size>([&](auto i) { (*this)[i] *= b; });
		return *this;
	}

	VecBase &operator*=(const VecBase &b) {
		unroll<Size>([&](auto i) { (*this)[i] *= b[i]; });
		return *this;
	}

	friend VecBase operator/(const VecBase &a, const VecBase &b) {
		for (int i = 0; i < Size; i++) {
			assert(b[i] != T(0));
		}
		VecBase result;
		unroll<Size>([&](auto i) { result[i] = a[i] / b[i]; });
		return result;
	}

	friend VecBase operator/(const VecBase &a, T b) {
		assert(b != T(0));
		VecBase result;
		unroll<Size>([&](auto i) { result[i] = a[i] / b; });
		return result;
	}

	friend VecBase operator/(T a, const VecBase &b) {
		for (int i = 0; i < Size; i++) {
			assert(b[i] != T(0));
		}
		VecBase result;
		unroll<Size>([&](auto i) { result[i] = a / b[i]; });
		return result;
	}

	VecBase &operator/=(T b) {
		assert(b != T(0));
		unroll<Size>([&](auto i) { (*this)[i] /= b; });
		return *this;
	}

	VecBase &operator/=(const VecBase &b) {
		assert(b != T(0));
		unroll<Size>([&](auto i) { (*this)[i] /= b[i]; });
		return *this;
	}

	/** Compare. */

	friend bool operator==(const VecBase &a, const VecBase &b) {
		for (int i = 0; i < Size; i++) {
			if (a[i] != b[i]) {
				return false;
			}
		}
		return true;
	}

	friend bool operator!=(const VecBase &a, const VecBase &b) {
		return !(a == b);
	}

	friend std::ostream &operator<<(std::ostream &stream, const VecBase &vec) {
		stream << "(";
		for (int i = 0; i < Size; i++) {
			stream << vec[i];
			if (i < Size - 1) {
				stream << ", ";
			}
		}

		stream << ")";
		return stream;
	}
};

}  // namespace revlab

using char2 = revlab::VecBase<int8_t, 2>;
using char3 = revlab::VecBase<int8_t, 3>;
using char4 = revlab::VecBase<int8_t, 4>;

using uchar3 = revlab::VecBase<uint8_t, 3>;
using uchar4 = revlab::VecBase<uint8_t, 4>;

using int2 = revlab::VecBase<int32_t, 2>;
using int3 = revlab::VecBase<int32_t, 3>;
using int4 = revlab::VecBase<int32_t, 4>;

using uint2 = revlab::VecBase<uint32_t, 2>;
using uint3 = revlab::VecBase<uint32_t, 3>;
using uint4 = revlab::VecBase<uint32_t, 4>;

using short2 = revlab::VecBase<int16_t, 2>;
using short3 = revlab::VecBase<int16_t, 3>;
using short4 = revlab::VecBase<int16_t, 4>;

using ushort2 = revlab::VecBase<uint16_t, 2>;
using ushort3 = revlab::VecBase<uint16_t, 3>;
using ushort4 = revlab::VecBase<uint16_t, 4>;

using float1 = revlab::VecBase<float, 1>;
using float2 = revlab::VecBase<float, 2>;
using float3 = revlab::VecBase<float, 3>;
using float4 = revlab::VecBase<float, 4>;

using double2 = revlab::VecBase<double, 2>;
using double3 = revlab::VecBase<double, 3>;
using double4 = revlab::VecBase<double, 4>;
