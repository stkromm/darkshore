#pragma once

#include <string>
#include <functional>
#include <vector>

#include "zlib/miniz.h"

static bool decompress(const char* source, std::vector<unsigned char>& dest, std::size_t inSize, std::size_t expectedSize)
{
	if (!source)
	{
		//LOG("Input string is empty, decompression failed.", Logger::Type::Error);
		return false;
	}

	int currentSize = static_cast<int>(expectedSize);
	std::vector<unsigned char> byteArray(expectedSize / sizeof(unsigned char));
	z_stream stream;
	stream.zalloc = Z_NULL;
	stream.zfree = Z_NULL;
	stream.opaque = Z_NULL;
	stream.next_in = (Bytef*)source;
	stream.avail_in = static_cast<unsigned int>(inSize);
	stream.next_out = (Bytef*)byteArray.data();
	stream.avail_out = static_cast<unsigned int>(expectedSize);

	//we'd prefer to use inflateInit2 but it appears 
	//to be incorrect in miniz. This is fine for zlib
	//compressed data, but gzip compressed streams
	//will fail to inflate. IMO still preferable to
	//trying to build/link zlib
	if (inflateInit(&stream/*, 15 + 32*/) != Z_OK)
	{
		//LOG("inflate init failed", Logger::Type::Error);
		return false;
	}

	int result = 0;
	do
	{
		result = inflate(&stream, Z_SYNC_FLUSH);

		switch (result)
		{
		case Z_NEED_DICT:
		case Z_STREAM_ERROR:
			result = Z_DATA_ERROR;
		case Z_DATA_ERROR:
			//Logger::log("If using gzip compression try using zlib instead", Logger::Type::Info);
		case Z_MEM_ERROR:
			inflateEnd(&stream);
			//dsmap::Logger::log(std::to_string(result), Logger::Type::Error);
			return false;
		}

		if (result != Z_STREAM_END)
		{
			int oldSize = currentSize;
			currentSize *= 2;
			std::vector<unsigned char> newArray(currentSize / sizeof(unsigned char));
			std::memcpy(newArray.data(), byteArray.data(), currentSize / 2);
			byteArray = std::move(newArray);

			stream.next_out = (Bytef*)(byteArray.data() + oldSize);
			stream.avail_out = oldSize;

		}
	} while (result != Z_STREAM_END);

	if (stream.avail_in != 0)
	{
		//LOG("stream.avail_in is 0", Logger::Type::Error);
		//LOG("zlib decompression failed.", Logger::Type::Error);
		return false;
	}

	const int outSize = currentSize - stream.avail_out;
	inflateEnd(&stream);

	std::vector<unsigned char> newArray(outSize / sizeof(unsigned char));
	std::memcpy(newArray.data(), byteArray.data(), outSize);
	byteArray = std::move(newArray);

	//copy bytes to vector
	dest.insert(dest.begin(), byteArray.begin(), byteArray.end());

	return true;
}

static std::string base64_decode(std::string const& encoded_string)
{
	static const std::string base64_chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";

	std::function<bool(unsigned char)> is_base64 =
		[](unsigned char c)->bool
	{
		return (isalnum(c) || (c == '+') || (c == '/'));
	};

	auto in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_]))
	{
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i == 4)
		{
			for (i = 0; i < 4; i++)
			{
				char_array_4[i] = static_cast<unsigned char>(base64_chars.find(char_array_4[i]));
			}
			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
			{
				ret += char_array_3[i];
			}
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 4; j++)
		{
			char_array_4[j] = 0;
		}

		for (j = 0; j < 4; j++)
		{
			char_array_4[j] = static_cast<unsigned char>(base64_chars.find(char_array_4[j]));
		}

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++)
		{
			ret += char_array_3[j];
		}
	}

	return ret;
}
