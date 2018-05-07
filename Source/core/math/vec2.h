#pragma once

#include "core/math/vine_math.h"

namespace math
{
	template<class T>
	struct Vec2
	{
		T x;
		T y;
	};

	struct FVec2;
	constexpr FVec2 abs(FVec2 vec);
	constexpr FVec2 add(const FVec2& a, const FVec2& b);
	constexpr float dot(const FVec2& a, const FVec2& b);
	struct FVec2
	{
		float x;
		float y;

		constexpr FVec2(const float x, const float y) : x(x), y(y)
		{
		}

		constexpr FVec2() : x(0), y(0)
		{
		}

		constexpr FVec2(const FVec2& copy) = default;

		explicit constexpr FVec2(const FVec2* copy) : x(copy->x), y(copy->y)
		{
		}

		explicit constexpr FVec2(float* data) : x(data[0]), y(data[1])
		{
		};

		FVec2 perpendicular() const { return { x, -y }; }

		constexpr FVec2 operator*(const float scale) const { return FVec2(x * scale, y * scale); }

		constexpr float operator*(const FVec2& other) const { return x * other.x + y * other.y; }

		constexpr FVec2 operator+(const FVec2& other) const { return add(*this, other); }

		constexpr void operator+=(const FVec2& other)
		{
			x += other.x;
			y += other.y;
		}

		constexpr FVec2 operator-(const FVec2& other) const { return FVec2(x - other.x, y - other.y); }

		constexpr float length() const { return sqrt(*this * *this); }
	};

	constexpr FVec2 add(const FVec2& a, const FVec2& b) { return FVec2(a.x + b.x, a.y + b.y); }
	constexpr float dot(const FVec2& a, const FVec2& b) { return a.x * b.x + a.y * b.y; }

	constexpr FVec2 abs(const FVec2 vec)
	{
		return { abs(vec.x), abs(vec.y) };
	}

	constexpr bool is_nearly_zero(const FVec2 vec)
	{
		return is_nearly_zero(vec.x) && is_nearly_zero(vec.y);
	}

	constexpr FVec2 clamp(const FVec2 vec, const float max)
	{
		return { math::clamp(vec.x, max), math::clamp(vec.y, max) };
	}

	constexpr FVec2 clamp(const FVec2 vec, const float max_x, const float max_y)
	{
		return { math::clamp(vec.x, max_x), math::clamp(vec.y, max_y) };
	}

	constexpr FVec2 clamp_positive(const FVec2 vec)
	{
		return { math::clamp_positive(vec.x), math::clamp_positive(vec.y) };
	}
}
