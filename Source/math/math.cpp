#pragma once
#include "vine_math.h"

#include <inttypes.h>

using namespace math;

//https://stackoverflow.com/questions/8622256/in-c11-is-sqrt-defined-as-constexpr
template <typename T>
constexpr T sqrt_helper(T x, T lo, T hi)
{
	if (lo == hi)
		return lo;

	const T mid = (lo + hi + 1) / 2;

	if (x / mid < mid)
		return sqrt_helper<T>(x, lo, mid - 1);
	else
		return sqrt_helper(x, mid, hi);
}

template<typename T> constexpr T sqrt(T x)
{
	return sqrt_helper<T>(x, 0, x / 2 + 1);
}