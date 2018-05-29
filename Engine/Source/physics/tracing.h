#pragma once
#include "core/math/vec2.h"
#include <vector>
#include "physics/private/intersection.h"

template<typename T>
struct Intersection
{
	T intersected_element;
	math::Vec2<float> point;
	math::Vec2<float> normal;
};

template<typename T>
struct TraceResult
{
	std::vector<Intersection<T>> intersected_elements;
};

template<typename T, typename R>
bool line_trace_aabbs(math::Vec2<float> start_point, math::Vec2<float> direction, float length, std::vector<const T> traces_elements, TraceResult<T>* result)
{
	for(auto& element : traces_elements)
	{
		physics::intersection::IntersectionData data;
	}
	return false;
}
