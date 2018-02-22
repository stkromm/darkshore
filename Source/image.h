#pragma once

#include <string>

#include "types.h"

struct RGBAColor {
private:
	unsigned int rgba;
public:
	constexpr RGBAColor(unsigned int color) : rgba(color) {}
	constexpr int color() {
		return rgba;
	}
	constexpr byte red() {
		return (byte)(rgba >> 24 & 0xFF);
	}
	constexpr byte green() {
		return (byte)(rgba >> 16 & 0xFF);
	}
	constexpr byte blue() {
		return (byte)(rgba >> 8 & 0xFF);
	}
	constexpr byte alpha() {
		return (byte)(rgba & 0xFF);
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
		return { *((unsigned int*)pixels + index) };
	}
};