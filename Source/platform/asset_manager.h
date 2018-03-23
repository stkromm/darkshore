#pragma once
#include <string>
#include <unordered_map>
#include <memory>

#include "asset_types.h"
#include "asset.h"

class AssetManager
{
	static std::unordered_map<AssetType, std::unordered_map<std::string, std::shared_ptr<Asset>>> loaded_assets;

public:
	static bool init();

	static void clean();

	template <class T>
	static std::shared_ptr<T> load_asset(std::string name)
	{
		auto asset_ref = loaded_assets[T::get_resource_type()].find(name);
		if (asset_ref != loaded_assets[T::get_resource_type()].end())
		{
			return std::static_pointer_cast<T>(asset_ref->second);
		}
		std::shared_ptr<T> loaded = std::make_shared<T>(name);
		loaded_assets[T::get_resource_type()][name] = loaded;
		return loaded;
	}
};
