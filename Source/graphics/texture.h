#pragma once

#include <string>
#include <memory>

#include "platform/asset.h"
#include "platform/asset_types.h"
#include "core/types.h"

namespace graphics
{
	class Texture : public Asset
	{
	private:
		uint32_t id = 0;
		const std::string file_path;

		uint32_t width, height;
	public:
		static AssetType get_resource_type()
		{
			return IMAGE;
		}

		explicit Texture(const std::string& file_path);
		explicit Texture(const uint32_t width, const uint32_t height, byte* data);
		~Texture();

		void bind(uint32_t slot = 0) const;
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

		void update_data(byte* data);
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
