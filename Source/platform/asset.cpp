#include "asset.h"

std::unordered_map<AssetType, std::unordered_map<std::string, std::shared_ptr<Asset>>> AssetManager::loaded_assets
= {};