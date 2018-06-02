#pragma once

#include <sstream>

namespace ds {
	namespace scene {
		struct Vertex
		{
			float x;
			float y;
			float tc_x;
			float tc_y;
			uint32_t texture_id;
			uint32_t tint;

			std::string to_string() const
			{
				std::stringstream sstream;
				sstream << "(" << x << "," << y << "," << tc_x << "," << tc_y << "," << tint << ")";
				return sstream.str();
			}
		};
	}
}