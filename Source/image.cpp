#include "image.h"

#include <iostream>
#include <vector>

#include "stb_image.h"

RGBAImage::RGBAImage(const std::string path, const char channel_count) {
	int t_x, t_y, t_n;
	stbi_set_flip_vertically_on_load(1);
	pixels = stbi_load(get_res_folder_path(AssetType::IMAGE, path).c_str(), &t_x, &t_y, &t_n, channel_count);
	/*ResourceHandle resource_handle = ResourceHandle(path);
	size_t size = resource_handle.get_byte_size();
	byte* buffer = new byte[size];
	resource_handle.get_file_raw(buffer, size);
	stbi_loadf_from_memory(buffer, size, &t_x, &t_y, &t_n, channel_count);
	*/
	x = t_x;
	y = t_y;
	n = t_n;
}

RGBAImage::~RGBAImage() {
	stbi_image_free(pixels);
}
