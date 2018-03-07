#pragma once
#include <string>

#include "platform/resource_handle.h"
#include "SFML/Audio.hpp"

class InputStream : public sf::InputStream {
	ResourceHandle resource_handle;
public:
	InputStream(ResourceHandle resource_handle) : resource_handle(resource_handle)
	{
	}

	////////////////////////////////////////////////////////////
	/// \brief Read data from the stream
	///
	/// After reading, the stream's reading position must be
	/// advanced by the amount of bytes read.
	///
	/// \param data Buffer where to copy the read data
	/// \param size Desired number of bytes to read
	///
	/// \return The number of bytes actually read, or -1 on error
	///
	////////////////////////////////////////////////////////////
	signed long long read(void* data, signed long long size) override
	{
		resource_handle.get_file_raw(data, (size_t)size);
	}

	////////////////////////////////////////////////////////////
	/// \brief Change the current reading position
	///
	/// \param position The position to seek to, from the beginning
	///
	/// \return The position actually sought to, or -1 on error
	///
	////////////////////////////////////////////////////////////
	signed long long seek(signed long long position) override
	{

	}

	////////////////////////////////////////////////////////////
	/// \brief Get the current reading position in the stream
	///
	/// \return The current position, or -1 on error.
	///
	////////////////////////////////////////////////////////////
	signed long long tell() override
	{

	}

	////////////////////////////////////////////////////////////
	/// \brief Return the size of the stream
	///
	/// \return The total number of bytes available in the stream, or -1 on error
	///
	////////////////////////////////////////////////////////////
	signed long long getSize() override
	{

	}
};
