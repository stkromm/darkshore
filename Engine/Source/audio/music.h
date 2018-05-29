#pragma once
#include <string>

namespace ds
{
	namespace audio
	{
		namespace BackgroundMusic
		{
			void play(const std::string& path, float fade_in = 0);
			void set_volume(float volume);
			void resume(float fade_in = 0);
			void pause(float fade_out = 0);
			void stop(float fade_out = 0);
		}
	}
}
