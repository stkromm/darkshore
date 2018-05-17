#pragma once

#include <string>
#include "core/platform/asset_types.h"

std::string get_res_folder_path(AssetType type, const std::string& name);

struct ResourceHandle
{
private:
	std::string resource_path;
	bool use_blob = false;

public:
	explicit ResourceHandle(std::string resource_path);

	std::string get_name() const
	{
		return resource_path;
	}

	void get_file_raw(void* data, size_t size) const;

	uint32_t get_byte_size() const
	{
		return 0;
	}

	std::string get_file_text() const
	{
		return "";
	}
};
