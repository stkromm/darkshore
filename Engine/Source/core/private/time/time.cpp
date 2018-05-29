#include "core/time/time.h"

#ifdef _WIN32

#include "windows.h"

static bool init = false;
static long long frequency;

static long long get_frequency()
{
	if(!init)
	{
		LARGE_INTEGER Frequency;
		QueryPerformanceFrequency(&Frequency);
		frequency = Frequency.QuadPart;
	}
	return frequency;
}

Timestamp::Timestamp()
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	ticks = time.QuadPart;
}

long Timestamp::operator-(const Timestamp start_timestamp) const
{
	const long long elapsed_ticks = ticks - start_timestamp.ticks;
	return long((elapsed_ticks * long long(1000000)) / get_frequency());
}

void Timestamp::operator+=(const float microseconds)
{
	this->ticks += (microseconds*get_frequency() /1000000);
}

uint64_t microseconds_since_epoch()
{
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	return (t.QuadPart * long long(1000000)) / get_frequency();
}
#else

#endif