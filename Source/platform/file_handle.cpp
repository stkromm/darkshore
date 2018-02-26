#include "file_handle.h"
#include "asset.h"

std::string get_res_folder_path(AssetType type, std::string name)
{
	std::stringstream string_stream;
	string_stream << "res/";
	switch (type) {
	case AssetType::IMAGE:
		string_stream << "image"; break;
	case AssetType::SOUND:
		string_stream << "sound"; break;
	case AssetType::MAP:
		string_stream << "map"; break;
	case AssetType::SHADER:
		string_stream << "shader"; break;
	case AssetType::SCRIPT:
		string_stream << "script"; break;
	case AssetType::FONT:
		string_stream << "font"; break;
	default:
		assert(false);
	}
	string_stream << "/" << name;
	return string_stream.str();
}