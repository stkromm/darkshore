#pragma once


namespace ds
{
	constexpr float PI = 3.14159265358f;
	constexpr float TWO_PI = PI * 2;
	constexpr float HALF_PI = PI * 0.5f;
	constexpr float FLOAT_ACCURACY = 0.e6f;

	constexpr float to_radians(const float degrees) { return float(degrees * (PI * (1 / 180.0f))); }
	constexpr float to_degrees(const float radians) { return float(radians * (180.0f * (1 / PI))); }

	constexpr bool is_nearly_zero(const float val)
	{
		return val < FLOAT_ACCURACY && val > -FLOAT_ACCURACY;
	}

	template<typename T>
	constexpr T lerp(const T a, const T b, const T lerp)
	{
		return a + (b - a) * lerp;
	}

	template<typename T>
	constexpr T abs(T val)
	{
		return val > 0.f ? val : -val;
	}

	template<typename  T>
	constexpr T clamp(T val, T max)
	{
		return val <= max ? val : max;
	}

	template<typename  T>
	constexpr T clamp_positive(T val)
	{
		return val >= 0 ? val : 0;
	}

	template <typename T>
	constexpr T sqrt(T x)
	{
		return sqrtf(x);
	}

	template <typename T>
	constexpr T invert(T x, T max)
	{
		return max - x;
	}

	template <typename T>
	constexpr T pow2(T base)
	{
		return base * base;
	}
}
