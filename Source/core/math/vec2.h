#pragma once

#include "core/math/vine_math.h"

namespace math {
	struct Vec2;

	constexpr Vec2 abs(const Vec2 vec);
	constexpr Vec2 add(const Vec2& a, const Vec2& b);
	constexpr float dot(const Vec2& a, const Vec2& b);

	struct Vec2 {
		float x;
		float y;

		constexpr Vec2(float x, float y) : x(x), y(y) {}
		constexpr Vec2() : x(0), y(0) {}
		constexpr Vec2(const Vec2& copy) : x(copy.x), y(copy.y) {}
		constexpr Vec2(const Vec2* copy) : x(copy->x), y(copy->y) {}
		constexpr Vec2(float* data) : x(data[0]), y(data[1]) {};

		Vec2 perpendicular() { Vec2(x, -y); }

		constexpr Vec2 operator*(const float scale) const { return  Vec2(x*scale, y*scale); }

		constexpr float operator*(const Vec2& other) const { return  x * other.x + y * other.y; }

		constexpr Vec2 operator+(const Vec2& other) const { return add(*this, other); }
		constexpr void operator+=(const Vec2& other) { x += other.x; y += other.y; }

		constexpr Vec2 operator-(const Vec2& other) const { return Vec2(x - other.x, y - other.y); }

		constexpr float length() const { return math::sqrt(*this * *this); }
	};
	constexpr Vec2 add(const Vec2& a, const Vec2& b) { return Vec2(a.x + b.x, a.y + b.y); }
	constexpr float dot(const Vec2& a, const Vec2& b) { return a.x * b.x + a.y * b.y; }

	constexpr Vec2 abs(const Vec2 vec)
	{
		return Vec2{ abs(vec.x), abs(vec.y) };
	}
	constexpr bool is_nearly_zero(Vec2 vec) {
		return is_nearly_zero(vec.x) && is_nearly_zero(vec.y);
	}
}