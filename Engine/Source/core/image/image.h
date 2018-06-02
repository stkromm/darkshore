#pragma once

#include <string>

#include "core/types.h"

namespace ds {
	struct RGBAColor
	{
	private:
		union {
			uint32_t rgba;
			byte channel[4];
		};
	public:
		RGBAColor(const uint32_t color) : rgba(color)
		{
		}

		constexpr int color() const
		{
			return rgba;
		}
	};

	struct RGBAImage
	{
	private:
		uint32_t x, y, n;
		byte* pixels;
	public:
		explicit RGBAImage(const std::string& path);
		~RGBAImage();

		uint32_t get_width() const
		{
			return x;
		}

		uint32_t get_height() const
		{
			return y;
		}

		uint32_t get_channel_count() const
		{
			return n;
		}

		byte* get_pixels() const
		{
			return pixels;
		}

		uint32_t get_size() const
		{
			return x * y;
		}

		RGBAColor operator[](const size_t index) const
		{
			return { *(reinterpret_cast<uint32_t*>(pixels) + index) };
		}
	};
}