#include "platform/asset_manager.h"

#include <iostream>

std::unordered_map<AssetType, std::unordered_map<std::string, std::shared_ptr<Asset>>> AssetManager::loaded_assets
= {};

bool AssetManager::init()
{
	return true;
}

void AssetManager::clean()
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