#pragma once

#include "core/math/vec2.h"
#include "core/math/vec3.h"
#include "core/types.h"

#undef near
#undef far

namespace math {
	constexpr size_t SIZE = 4 * 4;
	struct Mat4x4
	{
	private:
		float elements[SIZE];

	public:
		Mat4x4(const float* elements)
		{
			memcpy(this->elements, elements, SIZE * sizeof(float));
		}

		Mat4x4(float diagonal)
		{
			memset(elements, 0, SIZE * sizeof(float));
			elements[0 + 0 * 4] = diagonal;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;
		}

		Mat4x4(const float e0, const float e1, const float e2, const float e3,
			const float e4, const float e5, const float e6, const float e7,
			const float e8, const float e9, const float e10, const float e11,
			const float e12, const float e13, const float e14, const float e15)
		{
			elements[0] = e0;
			elements[1] = e1;
			elements[2] = e2;
			elements[3] = e3;

			elements[4] = e4;
			elements[5] = e5;
			elements[6] = e6;
			elements[7] = e7;

			elements[8] = e8;
			elements[9] = e9;
			elements[10] = e10;
			elements[11] = e11;

			elements[12] = e12;
			elements[13] = e13;
			elements[14] = e14;
			elements[15] = e15;
		}

		Mat4x4(const ConstVec3& c0, const ConstVec3& c1, const ConstVec3& c2)
		{
			memset(elements, 0, SIZE * sizeof(float));
			elements[0] = c0.x;
			elements[1] = c0.y;
			elements[2] = c0.z;

			elements[4] = c0.x;
			elements[5] = c0.y;
			elements[6] = c0.z;

			elements[8] = c0.x;
			elements[9] = c0.y;
			elements[10] = c0.z;

			elements[15] = 1;
		}

		float operator[](const size_t index) const
		{
			return elements[index];
		}

		Mat4x4 operator+(const Mat4x4 other) const
		{
			return Mat4x4(
				elements[4 * 0 + 0] + other[4 * 0 + 0],
				elements[4 * 0 + 1] + other[4 * 0 + 1],
				elements[4 * 0 + 2] + other[4 * 0 + 2],
				elements[4 * 0 + 3] + other[4 * 0 + 3],

				elements[4 * 1 + 0] + other[4 * 1 + 0],
				elements[4 * 1 + 1] + other[4 * 1 + 1],
				elements[4 * 1 + 2] + other[4 * 1 + 2],
				elements[4 * 1 + 3] + other[4 * 1 + 3],

				elements[4 * 2 + 0] + other[4 * 2 + 0],
				elements[4 * 2 + 1] + other[4 * 2 + 1],
				elements[4 * 2 + 2] + other[4 * 2 + 2],
				elements[4 * 2 + 3] + other[4 * 2 + 3],

				elements[4 * 3 + 0] + other[4 * 3 + 0],
				elements[4 * 3 + 1] + other[4 * 3 + 1],
				elements[4 * 3 + 2] + other[4 * 3 + 2],
				elements[4 * 3 + 3] + other[4 * 3 + 3]
			);
		}

		Mat4x4 operator*(const Mat4x4 other) const
		{
			float data[16]{};
			for (size_t row = 0; row < 4; row++)
			{
				for (size_t col = 0; col < 4; col++)
				{
					float sum = 0.0f;
					sum += elements[0 + row * 4] * other.elements[col + 0 * 4];
					sum += elements[1 + row * 4] * other.elements[col + 1 * 4];
					sum += elements[2 + row * 4] * other.elements[col + 2 * 4];
					sum += elements[3 + row * 4] * other.elements[col + 3 * 4];
					data[col + row * 4] = sum;
				}
			}
			return Mat4x4(data);
		}

		void set_rotation(float rotation)
		{
			float cos_phi = cosf(rotation);
			float sin_phi = sinf(rotation);
			elements[0] = cos_phi;
			elements[4] = -sin_phi;
			elements[1] = sin_phi;
			elements[5] = cos_phi;
		}

		void set_translation(float x, float y, float z)
		{
			elements[3 * 4] = x;
			elements[3 * 4 + 1] = y;
			elements[3 * 4 + 2] = z;
		}

		void scale(float x, float y, float z)
		{
			elements[0] *= x;
			elements[5] *= y;
			elements[10] *= z;
		}
		void set_translation(math::Vec3 translation)
		{
			set_translation(translation.x, translation.y, translation.z);
		}

		Mat4x4 orthographic(const float left, const float right, const  float bottom, const float top, const float near, const float far) const
		{
			Mat4x4 result(1.0f);

			result.elements[0 + 0 * 4] = 2.0f / (right - left);

			result.elements[1 + 1 * 4] = 2.0f / (top - bottom);

			result.elements[2 + 2 * 4] = 2.0f / (near - far);

			result.elements[3 + 0 * 4] = (left + right) / (left - right);
			result.elements[3 + 1 * 4] = (bottom + top) / (bottom - top);
			result.elements[3 + 2 * 4] = (far + near) / (far - near);

			return result;
		}

		Mat4x4 perspective(const float fov, const float aspectRatio, const float near, const float far) const
		{
			Mat4x4 result(1.0f);

			const float q = 1.0f / tan(to_radians(0.5f * fov));
			const float a = q / aspectRatio;

			const float b = (near + far) / (near - far);
			const float c = (2.0f * near * far) / (near - far);

			result.elements[0 + 0 * 4] = a;
			result.elements[1 + 1 * 4] = q;
			result.elements[2 + 2 * 4] = b;
			result.elements[2 + 3 * 4] = -1.0f;
			result.elements[3 + 2 * 4] = c;

			return result;
		}

		Mat4x4 look_at(const ConstVec3& camera, const ConstVec3& point, const ConstVec3& up) const
		{
			Mat4x4 result(1);
			const ConstVec3 f = (point - camera).normalize();
			const ConstVec3 s = f | up.normalize();
			const ConstVec3 u = s | f;

			result.elements[0 + 0 * 4] = s.x;
			result.elements[0 + 1 * 4] = s.y;
			result.elements[0 + 2 * 4] = s.z;

			result.elements[1 + 0 * 4] = u.x;
			result.elements[1 + 1 * 4] = u.y;
			result.elements[1 + 2 * 4] = u.z;

			result.elements[2 + 0 * 4] = -f.x;
			result.elements[2 + 1 * 4] = -f.y;
			result.elements[2 + 2 * 4] = -f.z;

			result.elements[3 + 0 * 4] = -camera.x;
			result.elements[3 + 1 * 4] = -camera.y;
			result.elements[3 + 2 * 4] = -camera.z;
			return result;
		}

		Mat4x4 lerp(Mat4x4 other, float lerp) {
			Mat4x4 result(1);
			result.elements[3 * 4] = math::lerp(elements[3 * 4], other.elements[3 * 4], lerp);
			result.elements[3 * 4 + 1] = math::lerp(elements[3 * 4 + 1], other.elements[3 * 4 + 1], lerp);
			result.elements[3 * 4 + 2] = math::lerp(elements[3 * 4 + 2], other.elements[3 * 4 + 2], lerp);

			return result;
		}

		float* data()
		{
			return elements;
		}

		String to_string() const {
			std::stringstream result;
			result << "Mat4x4(";
			for (size_t index = 0; index < 4; index++) {
				result
					<< "("
					<< elements[index * 4 + 0] << ","
					<< elements[index * 4 + 1] << ","
					<< elements[index * 4 + 2] << ","
					<< elements[index * 4 + 3]
					<< ")";
			}
			result << ")";
			return result.str();
		}
	};
}