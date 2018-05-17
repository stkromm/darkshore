#include "graphics/texture.h"

#include <iostream>

#include "graphics/graphics.h"
#include "core/image/image.h"
#include "core/logger/log.h"

namespace graphics
{
	Texture::Texture(const std::string& file_path) : file_path(file_path)
	{
		LOG_INFO << "Load texture: " << file_path << LOG_END;
		RGBAImage image = RGBAImage(file_path);
		GLCall(glGenTextures(1, &id));
		bind();

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.get_width(), image.get_height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
			image.get_pixels()));
		width = image.get_width();
		height = image.get_height();
	}

	Texture::Texture(const uint32_t width, const uint32_t height, byte* data) : width(width), height(height)
	{
		GLCall(glGenTextures(1, &id));
		bind();

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			data));
	}

	Texture::~Texture()
	{
		unbind();
		GLCall(glDeleteTextures(1,&id));
	}

	void Texture::bind(const uint32_t slot) const
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, id));
	}

	void Texture::unbind() const
	{
		LOG_INFO << "Unbind texture " << id << LOG_END;
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void Texture::update_data(byte* data)
	{
		bind();
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			data));
	}
}
