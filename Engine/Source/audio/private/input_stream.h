#pragma once
#include <utility>

#include "platform/resource_handle.h"
#include "third_party/sfml/Audio.hpp"

namespace ds {
	class InputStream : public sf::InputStream
	{
		ResourceHandle resource_handle;
	public:
		explicit InputStream(ResourceHandle resource_handle) : resource_handle(std::move(resource_handle))
		{
		}

		signed long long read(void* data, const signed long long size) override
		{
			resource_handle.get_file_raw(data, size_t(size));
			return 0;
		}

		signed long long seek(signed long long position) override
		{
			return 0;
		}

		signed long long tell() override
		{
			return 0;
		}

		signed long long getSize() override
		{
			return 0;
		}
	};
}