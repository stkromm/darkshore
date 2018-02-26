#pragma once

#include <string>
#include <sstream>
#include <assert.h>
#include <fstream>

#include "types.h"

enum AssetType;

std::string get_res_folder_path(AssetType type, std::string name);

struct ResourceHandle
{
	std::string resource_path;
	bool use_blob = false;

	ResourceHandle(std::string resource_path) : resource_path(resource_path)
	{
		if (use_blob)
		{

		}
		else
		{
		}
	}

	std::string get_name() const
	{

	}
	void get_file_raw(void* data, size_t size) const
	{
		std::fstream file_stream;
		file_stream.open(resource_path, std::ios::binary | std::ios::ate | std::ios::in);
		char* oData = 0;
		/*		size_t size = 0;
		file_stream.seekg(0, std::ios::end); // set the pointer to the end
		size = file_stream.tellg(); // get the length of the file
		file_stream.seekg(0, std::ios::beg); // set the pointer to the beginning

		oData = new char[size + 1]; //  for the '\0'
		file_stream.read(oData, size);
		oData[size] = '\0'; // set '\0'
		getchar();*/

	}

	unsigned int get_byte_size() const
	{
		return 0;
	}
	std::string get_file_text() const
	{

	}
};