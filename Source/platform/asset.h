#pragma once

#include <string>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <memory>

#include "platform/file_handle.h"

enum AssetType
{
	IMAGE, SOUND, MAP, SHADER, SCRIPT, FONT
};

class Asset
{

};

class AssetManager
{
	static std::unordered_map<AssetType, std::unordered_map<std::string, std::shared_ptr<Asset>>> loaded_assets;

public:
	static bool init()
	{
		AssetManager::loaded_assets[AssetType::SHADER] = std::unordered_map<std::string, std::shared_ptr<Asset>>();
		AssetManager::loaded_assets[AssetType::IMAGE] = std::unordered_map<std::string, std::shared_ptr<Asset>>();
		return true;
	}

	template<class T>
	static std::shared_ptr<T> load_asset(std::string name)
	{
		auto asset_ref = loaded_assets[T::get_resource_type()].find(name);
		if (asset_ref != loaded_assets[T::get_resource_type()].end())
		{
			return std::static_pointer_cast<T>(asset_ref->second);
		}
		else
		{
			std::shared_ptr<T> loaded = std::make_shared<T>(name);
			loaded_assets[T::get_resource_type()][name] = loaded;
			return loaded;
		}
	}

	static void clean()
	{
		for (auto& asset_map : loaded_assets)
		{
			if (asset_map.second.size() != 0)
				for (auto& asset_ref : asset_map.second)
				{
					if (!asset_ref.second.unique())
					{
						std::cout << asset_ref.first << std::endl;
					}
				}

		}
	}
};