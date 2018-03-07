#pragma once

#include <string>
#include <unordered_map>

struct Config
{
private:
	std::unordered_map<std::string, std::string> entries;
public:
	Config(std::string file_path)
	{

	}
};