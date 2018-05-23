#include "graphics/texture.h"

#include "graphics/graphics.h"
#include "core/image/image.h"
#include "core/logger/log.h"

namespace ds {
	namespace graphics
	{
		Texture::Texture(const std::string& file_path) : file_path(file_path)
		{
			RGBAImage image = RGBAImage(file_path);
			GLCall(glGenTextures(1, &id));
			bind();

			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

			width = image.get_width();
			height = image.get_height();
			LOG_INFO << "Creating texture width:" << width << "height:" << height << LOG_END;
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.get_width(), image.get_height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
				image.get_pixels()));
		}

		Texture::Texture(const uint32_t width, const uint32_t height, byte* data) : width(width), height(height)
		{
			GLCall(glGenTextures(1, &id));
			bind();

			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

			LOG_INFO << "Creating texture width:" << width << "height:" << height << LOG_END;
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
				data));
		}

		Texture::~Texture()
		{
			unbind();
			GLCall(glDeleteTextures(1, &id));
		}

		static uint32 last_bound_slot = -1;
		static uint32 last_bound_id = -1;


		void Texture::bind(uint32_t slot) const
		{
			if (last_bound_slot != slot || last_bound_id != id)
			{
				LOG_INFO << "Binding texture " << id << " on Slot " << slot << LOG_END;
				last_bound_slot = slot;
				last_bound_id = id;
				GLCall(glActiveTexture(GL_TEXTURE0 + slot));
				GLCall(glBindTexture(GL_TEXTURE_2D, id));
			}
		}

		void Texture::unbind() const
		{
			if (last_bound_id != 0)
			{
				last_bound_id = 0;
				LOG_INFO << "Unbind texture " << id << LOG_END;
				GLCall(glBindTexture(GL_TEXTURE_2D, 0));
			}
		}

		void Texture::update_data(byte* data)
		{
			bind();
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
				data));
		}
	}
}