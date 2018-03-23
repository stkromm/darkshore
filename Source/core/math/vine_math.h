#pragma once
#include "core/types.h"

namespace math
{
	constexpr float PI = 3.14159265358f;

	constexpr float to_radians(const float degrees) { return float(degrees * (PI * (1 / 180.0f))); }
	constexpr float to_degrees(const float radians) { return float(radians * (180.0f * (1 / PI))); }

	constexpr bool is_nearly_zero(const float val)
	{
		return val < 0.000001f && val > -0.000001f;
	}

	constexpr float lerp(const float a, const float b, const float lerp)
	{
		return a + (b - a) * lerp;
	}

	constexpr float abs(const float val)
	{
		return val > 0.f ? val : -val;
	}

	template <typename T>
	constexpr T sqrt(T x)
	{
		return sqrtf(x);
	}
}
