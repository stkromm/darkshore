#pragma once
#include <sstream>
#include <string>
#include <unordered_map>
#include <memory>

#include "asset_types.h"
#include "asset.h"
#include <cassert>
#include "core/logger/log.h"

namespace ds {
	class AssetManager
	{
		static std::unordered_map<AssetType, std::unordered_map<std::string, std::shared_ptr<Asset>>> loaded_assets;

	public:
		static std::string get_res_folder_path(const AssetType type, const std::string& name)
		{
			std::stringstream string_stream;
			string_stream << "res/";
			switch (type)
			{
			case IMAGE:
				string_stream << "image";
				break;
			case SOUND:
				string_stream << "sound";
				break;
			case MAP:
				string_stream << "map";
				break;
			case SHADER:
				string_stream << "shader";
				break;
			case SCRIPT:
				string_stream << "script";
				break;
			case FONT:
				string_stream << "font";
				break;
			default:
				assert(false);
			}
			string_stream << "/" << name;
			return string_stream.str();
		}

		static bool init();

		static void clean();

		template <class T>
		static std::shared_ptr<T> load_asset(resource identifier)
		{
			auto asset_ref = loaded_assets[T::get_resource_type()].find("basic.shader");
			if (asset_ref != loaded_assets[T::get_resource_type()].end())
			{
				return std::static_pointer_cast<T>(asset_ref->second);
			}
			std::shared_ptr<T> loaded = std::make_shared<T>("basic.shader");
			loaded_assets[T::get_resource_type()]["basic.shader"] = loaded;
			return loaded;
		}

		template <class T>
		static std::shared_ptr<T> load_asset(std::string name)
		{
			auto asset_ref = loaded_assets[T::get_resource_type()].find(name);
			if (asset_ref != loaded_assets[T::get_resource_type()].end())
			{
				return std::static_pointer_cast<T>(asset_ref->second);
			}
			LOG_INFO << "Load Asset " << get_res_folder_path(T::get_resource_type(), name) << LOG_END;
			std::shared_ptr<T> loaded = std::make_shared<T>(get_res_folder_path(T::get_resource_type(), name));
			loaded_assets[T::get_resource_type()][name] = loaded;
			return loaded;
		}
	};
}