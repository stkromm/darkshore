#include "core/time/time.h"

#include "windows.h"

Timestamp::Timestamp()
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	ticks = time.QuadPart;
}

long Timestamp::operator-(const Timestamp start_timestamp) const
{
	// TODO Query frequency once at start and save it as constant
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	const long long frequency = Frequency.QuadPart;

	const long long elapsed_ticks = ticks - start_timestamp.ticks;
	
	return long((elapsed_ticks * long long(1000000)) / frequency);
}

void Timestamp::operator+=(const float microseconds)
{
	// TODO Query frequency once at start and save it as constant
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	const long long frequency = Frequency.QuadPart;

	this->ticks += (microseconds*frequency /1000000);
}

uint64_t microseconds_since_epoch()
{
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);

	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	const long long frequency = Frequency.QuadPart;

	return (t.QuadPart * long long(1000000)) / frequency;
}

