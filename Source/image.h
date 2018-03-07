#pragma once

#include <string>

#include "core/types.h"
#include "platform/resource_handle.h"

struct RGBAColor {
private:
	uint32_t rgba;
public:
	constexpr RGBAColor(uint32_t color) : rgba(color) {}
	constexpr int color() {
		return rgba;
	}
};

struct RGBAImage {
private:
	uint32_t x, y, n;
	byte* pixels;
public:
	RGBAImage(const std::string path, const char channel_count = 4);
	~RGBAImage();

	inline uint32_t get_width() const {
		return x;
	}

	inline uint32_t get_height() const {
		return y;
	}

	inline uint32_t get_channel_count() const {
		return n;
	}

	inline byte* get_pixels() const {
		return pixels;
	}

	inline uint32_t get_size() const {
		return x*y;
	}

	RGBAColor operator[](size_t index) const {
		return { *((uint32_t*)pixels + index) };
	}
};