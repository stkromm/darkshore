#pragma once

namespace ds
{
	namespace graphics
	{
		using PlatformHandle = void*;

		class Context
		{
		public:
			PlatformHandle get_platform_handle();
		};
	}
}