#pragma once

#include "platform/asset.h"
#include "graphics/texture.h"

namespace ds {
	class TextureAsset : public Asset
	{
	public:
		static AssetType get_resource_type()
		{
			return IMAGE;
		}

		TextureAsset(std::string name) : texture(std::make_shared<ds::graphics::Texture>(name)) {}
		std::shared_ptr<ds::graphics::Texture> texture;
	};
}