#pragma once
#include "types.h"

namespace math {
	constexpr float PI = 3.14159265358f;

	//constexpr uint32_t bit(uint32_t digits) { return (uint32_t)((uint32_t)1 << digits); }

	template<typename T> constexpr T sqrt(T x);
	template<typename T> constexpr T inverse_sqrt(T x);
	template<typename T> constexpr T pow(T base, T exp);
	template<typename T> constexpr T exp(T x);

	template<typename T> constexpr T sin(T x);
	template<typename T> constexpr T cos(T x);
	template<typename T> constexpr T tan(T x);

	template<typename T> constexpr T fast_sin(T x);
	template<typename T> constexpr T fast_cos(T x);
	template<typename T> constexpr T fast_tan(T x);

	template<typename T> constexpr T atan(T x);
	template<typename T> constexpr T atan2(T x, T y);

	constexpr float to_radians(float degrees) { return (float)(degrees * (PI * (1 / 180.0f))); }
	constexpr float to_degrees(float radians) { return (float)(radians * (180.0f * (1 / PI))); }

	constexpr bool is_nearly_zero(float val)
	{
		return val < 0.000001f && val > -0.000001f;
	}

	constexpr float lerp(float a, float b, float lerp)
	{
		return a + (b - a) * lerp;
	}

	constexpr float abs(float val)
	{
		return val > 0.f ? val : -val;
	}
}