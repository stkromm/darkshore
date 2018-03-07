#pragma once

#include <string>
#include "platform/asset_types.h"

std::string get_res_folder_path(AssetType type, std::string name);

struct ResourceHandle
{
private:
	std::string resource_path;
	bool use_blob = false;

public:
	ResourceHandle(std::string resource_path);

	std::string get_name() const
	{

	}

	void get_file_raw(void* data, size_t size) const;

	uint32_t get_byte_size() const
	{
		return 0;
	}

	std::string get_file_text() const
	{

	}
};