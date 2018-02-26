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
		unsigned int id;
		const std::string file_path;

		unsigned int width, height;
	public:
		static AssetType get_resource_type()
		{
			return AssetType::IMAGE;
		}

		Texture(const std::string file_path);
		~Texture();

		void bind(const unsigned int slot = 0) const;
		void unbind() const;

		bool operator==(const Texture& texture) const
		{
			return texture.id == id;
		}

		unsigned int get_width() const
		{
			return width;
		}

		unsigned int get_height() const
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

