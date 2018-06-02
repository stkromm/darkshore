#pragma once
#include "platform/asset.h"
#include <memory>
#include "graphics/shader.h"
#include "platform/asset_types.h"

namespace ds {
	class ShaderAsset : public Asset
	{
	public:
		static AssetType get_resource_type()
		{
			return SHADER;
		}

		ShaderAsset(std::string name) : shader(std::make_shared<ds::graphics::Shader>(name)) {}
		std::shared_ptr<ds::graphics::Shader> shader;
	};
}