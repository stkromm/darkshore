#pragma once

#include <iostream>

namespace logger
{
struct log_end {};

struct stream
{
};

template<typename type>
stream& operator<<(stream& s, type value)
{
	std::cout << value;
	return s;
}

inline void operator<<(stream& s, log_end& end)
{
	std::cout << std::endl;
}

}

extern logger::log_end end;
extern logger::stream log_info;

#define LOG_INFO log_info
#define LOG_END end