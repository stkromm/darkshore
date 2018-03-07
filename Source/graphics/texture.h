#pragma once

#include <string>
#include <memory>

#include "graphics/graphics.h"
#include "platform/asset.h"
#include "image.h"

namespace graphics
{
	class Texture : public Asset
	{
	private:
		uint32_t id;
		const std::string file_path;

		uint32_t width, height;
	public:
		static AssetType get_resource_type()
		{
			return AssetType::IMAGE;
		}

		Texture(const std::string file_path);
		~Texture();

		void bind(const uint32_t slot = 0) const;
		void unbind() const;

		bool operator==(const Texture& texture) const
		{
			return texture.id == id;
		}

		uint32_t get_width() const
		{
			return width;
		}

		uint32_t get_height() const
		{
			return height;
		}
	};

	struct TexturePatch
	{
		std::shared_ptr<Texture> texture;
		float x1;
		float y1;
		float x2;
		float y2;
	};

}

