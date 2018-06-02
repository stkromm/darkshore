#pragma once
#include "core/types.h"
#include "vec2.h"

namespace ds
{
	template <typename T>
	struct Mat3x3
	{
		union
		{
			T elements_vec[9];
			struct
			{
				T e1, e2, e3, e4, e5, e6, e7, e8, e9;
			};
		} elements;

		Vec2<T> transform(Vec2<T> transformed)
		{
			T x = elements.elements_vec[0] * transformed.x;
			T y = elements.elements_vec[1] * transformed.x;
			x += elements.elements_vec[3] * transformed.y;
			y += elements.elements_vec[4] * transformed.y;
			x += elements.elements_vec[6];
			y += elements.elements_vec[7];
			return std::move({ x,y });
		}
	};
}
