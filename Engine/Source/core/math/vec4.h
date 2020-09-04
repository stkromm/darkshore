#pragma once
#include "vec3.h"

namespace ds
{
	template<typename T>
	struct Vec4
	{
		union xyz {
			struct {
				T x;
				T y;
				T z;
			};
			Vec3 vec;
		} xyz;
		T w;

		Vec4(T x, T y, T z, T w) : xyz(x, y, z), w(w) {}
		Vec4(const Vec3& point, T w = 1) : xyz(point.x, point.y, point.z), w(w) {}
		Vec4(Vec3&& point, T w = 1) : xyz(point), w(w) {}
	};
}
