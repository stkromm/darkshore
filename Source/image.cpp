#include "image.h"
#include "stb_image.h"

#include <iostream>
#include <vector>

RGBAImage::RGBAImage(const std::string path, const char channel_count) {
	int t_x, t_y, t_n;
	stbi_set_flip_vertically_on_load(1);
	pixels = stbi_load(path.c_str(), &t_x, &t_y, &t_n, channel_count);

	x = t_x;
	y = t_y;
	n = t_n;
}

RGBAImage::~RGBAImage() {
	stbi_image_free(pixels);
}
