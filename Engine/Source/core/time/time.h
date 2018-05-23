#pragma once

#include "core/types.h"

/**
 * System local timestamp in microseconds
 */
struct Timestamp
{	
private:
	long long ticks;
public:
	Timestamp();
	long operator-(Timestamp start_timestamp) const;
	bool operator>(const Timestamp timestamp) const
	{
		return ticks > timestamp.ticks;
	}
	void operator+=(float ticks);
};


uint64_t microseconds_since_epoch();

