#pragma once

#include <string>

using Window_Handle = void*;

using byte = unsigned char;
using sbyte = char;

using int16 = short;
using uint16 = unsigned short;

/**
 * Big endian
 */
using int32 = int_fast32_t;
using uint32 = uint_fast32_t;

/**
 * IEEE 754
 */
using float32 = float;
using float64 = double;