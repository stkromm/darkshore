#pragma once

#include <sstream>

struct Vertex
{
	float x;
	float y;
	float tc_x;
	float tc_y;
	uint32_t color;

	std::string to_string() const
	{
		std::stringstream sstream;
		sstream << "(" << x << "," << y << "," << tc_x << "," << tc_y << "," << color << ")";
		return sstream.str();
	}
};
