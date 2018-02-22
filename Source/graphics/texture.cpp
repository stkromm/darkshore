#include "texture.h"

#include <iostream>

namespace graphics {
	Texture::Texture(std::string file_path) : file_path(file_path)
	{
		RGBAImage image = RGBAImage(file_path);
		GLCall(glGenTextures(1, &id));
		bind();

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.get_width(), image.get_height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.get_pixels()));
		width = image.get_width();
		height = image.get_height();

	};

	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1,&id));
	}

	void Texture::bind(const unsigned int slot) const {
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, id));
	}

	void Texture::unbind() const {
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
}
