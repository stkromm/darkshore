#pragma once

#include "core/math/vine_math.h"

namespace ds
{
	template<class T>
	constexpr T cross2D(const T x1, const T y1, const T x2, const T y2)
	{
		return x1 * y2 - x2 * y1;
	}

	template<class T>
	constexpr T dot(const T x1, const T y1, const T x2, const T y2)
	{
		return x1 * x2 + y1 * y2;
	}

	template<class T>
	constexpr T squared_length(const T x, const T y)
	{
		return x * x + y * y;
	}

	template<class T>
	constexpr T length(const T x, const T y)
	{
		return sqrt(squared_length(x, y));
	}

	template<class T>
	struct Vec2
	{
		T x;
		T y;

		constexpr Vec2(const T x, const T y) : x(x), y(y)
		{
		}

		constexpr Vec2() : x(0), y(0)
		{
		}

		constexpr Vec2(const Vec2& copy) = default;

		explicit constexpr Vec2(const Vec2* copy) : x(copy->x), y(copy->y)
		{
		}

		explicit constexpr Vec2(T* data) : x(data[0]), y(data[1])
		{
		};

		Vec2 perpendicular() const { return { x, -y }; }

		constexpr Vec2 operator*(const float scale) const { return { x * scale, y * scale }; }

		constexpr T operator*(const Vec2& other) const { return x * other.x + y * other.y; }

		constexpr void operator*=(const T factor)
		{
			x *= factor;
			y *= factor;
		}

		constexpr Vec2 operator+(const Vec2& other) const { return { x + other.x, y + other.y }; }

		constexpr Vec2 operator-(const Vec2& other) const { return { x - other.x, y - other.y }; }

		constexpr void operator+=(const Vec2& other)
		{
			x += other.x;
			y += other.y;
		}

		constexpr void set(const T x, const T y)
		{
			this->x = x;
			this->y = y;
		}

		constexpr void operator-=(const Vec2& other)
		{
			x -= other.x;
			y -= other.y;
		}

		constexpr T squared_length() const { return ds::squared_length(x, y); }
		constexpr T length() const { return ds::sqrt(ds::squared_length(x, y)); }

		constexpr void normalize()
		{
			T i_length = 1 / length();
			x *= i_length;
			y *= i_length;
		}

		constexpr T get_distance(const Vec2& other)
		{
			return length(x - other.x, y - other.y);
		}
	};

	template< typename T>
	T get_angle(Vec2<T> a, Vec2<T> b)
	{
		if (is_nearly_zero(a) || is_nearly_zero(b))
		{
			return 0.f;
		}

		const T dot = dot(a, b);
		if (is_nearly_zero(dot)) // Perpendicular
		{
			return HALF_PI;
		}
		const T cross = cross2D(a.x, a.y, b.x, b.y);
		if (is_nearly_zero(cross)) // Collinear
		{
			if (dot < FLOAT_ACCURACY)
			{
				return PI;
			}
			// Because we know the vectors are collinear, but not opposite
			// directions, they must have the same direction.
			else
			{
				return 0.f;
			}
		}
		T angle = std::atan2(cross, dot);
		if (angle > PI)
		{
			angle -= TWO_PI;
		}
		else if (angle < -PI)
		{
			angle += TWO_PI;
		}
		return angle;
	}
	using FVec2 = Vec2<float>;

	template< typename T>
	constexpr bool is_collinear(const Vec2<T> a, const Vec2<T> b)
	{
		return ds::is_nearly_zero(ds::cross2D(a.x, a.y, b.x, b.y));
	}

	template< typename T>
	constexpr Vec2<T> abs(const Vec2<T> vec)
	{
		return { ds::abs(vec.x), ds::abs(vec.y) };
	}

	template< typename T>
	constexpr bool is_nearly_zero(const Vec2<float> vec)
	{
		return is_nearly_zero(vec.x) && is_nearly_zero(vec.y);
	}

	constexpr bool is_nearly_zero(const FVec2 vec)
	{
		return is_nearly_zero(vec.x) && is_nearly_zero(vec.y);
	}

	template< typename T>
	constexpr Vec2<T> clamp(const Vec2<T> vec, const float max)
	{
		return { ds::clamp(vec.x, max), ds::clamp(vec.y, max) };
	}

	template< typename T>
	constexpr Vec2<T> clamp(const Vec2<T> vec, const float max_x, const float max_y)
	{
		return { ds::clamp(vec.x, max_x), ds::clamp(vec.y, max_y) };
	}

	template< typename T>
	constexpr Vec2<T> clamp_positive(const Vec2<T> vec)
	{
		return { ds::clamp_positive(vec.x), ds::clamp_positive(vec.y) };
	}
}