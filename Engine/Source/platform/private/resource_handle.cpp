#include "platform/resource_handle.h"

#include <sstream>
#include <cassert>
#include <fstream>
#include <utility>

using namespace ds;
std::string ds::get_res_folder_path(const AssetType type, const std::string& name)
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

ResourceHandle::ResourceHandle(std::string resource_path) : resource_path(std::move(resource_path))
{
	if (use_blob)
	{
	}
	else
	{
	}
}

void ResourceHandle::get_file_raw(void* data, size_t size) const
{
	std::fstream file_stream;
	file_stream.open(resource_path, std::ios::binary | std::ios::ate | std::ios::in);
	/*		size_t size = 0;
	file_stream.seekg(0, std::ios::end); // set the pointer to the end
	size = file_stream.tellg(); // get the length of the file
	file_stream.seekg(0, std::ios::beg); // set the pointer to the beginning

	oData = new char[size + 1]; //  for the '\0'
	file_stream.read(oData, size);
	oData[size] = '\0'; // set '\0'
	getchar();*/
}
