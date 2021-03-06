#pragma once

#include "core/math/vine_math.h"
#include <sstream>


namespace ds
{
	struct Vec3
	{
		float x;
		float y;
		float z;

		Vec3 operator+(const Vec3& other) const
		{
			return { x + other.x, y + other.y, z + other.z };
		}
	};

	struct ConstVec3
	{
		const float x;
		const float y;
		const float z;

		constexpr ConstVec3(const ConstVec3& copy) = default;

		constexpr ConstVec3(const float x, const float y, const float z) : x(x), y(y), z(z)
		{
		}

		explicit constexpr ConstVec3(float* data) : x(data[0]), y(data[1]), z(data[2])
		{
		}

		explicit constexpr ConstVec3(const Vec3& copy) : x(copy.x), y(copy.y), z(copy.z)
		{
		};

		/**
		Scalar product operator.
		*/
		constexpr float operator*(const ConstVec3& other) const
		{
			return x * other.x + y * other.y + z * other.z;
		}

		constexpr ConstVec3 operator*(const float scale) const
		{
			return ConstVec3(x * scale, y * scale, z * scale);
		}

		constexpr ConstVec3 operator+(const ConstVec3& other) const
		{
			return ConstVec3(x + other.x, y + other.y, z + other.z);
		}

		constexpr ConstVec3 operator-(const ConstVec3& other) const
		{
			return ConstVec3(x - other.x, y - other.y, z - other.z);
		}

		/**
		Cross product operator.
		*/
		constexpr ConstVec3 operator|(const ConstVec3& other) const
		{
			return ConstVec3(x * other.y - y * other.x, 0, 0);
		}

		constexpr float operator[](const int index) const
		{
			if (index <= 0)
			{
				return x;
			}
			if (index == 1)
			{
				return y;
			}
			return z;
		}

		constexpr ConstVec3 normalize() const
		{
			const float l = length();
			if (l != 0.f && l != 1.f)
			{
				const float inverseLength = 1 / l;
				return { x * inverseLength, y * inverseLength, z * inverseLength };
			}
			return { x, y, z };
		}

		constexpr float length() const
		{
			return sqrt(squared_length());
		}

		constexpr float squared_length() const
		{
			return *this * *this;
		}

		std::string to_string() const
		{
			std::stringstream result;
			result << "ConstVec3(" << x << "," << y << "," << z << ")";
			return result.str();
		}
	};
}
