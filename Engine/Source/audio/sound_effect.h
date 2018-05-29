#pragma once

#include "audio/private/input_stream.h"

namespace audio
{
	class SoundEffect
	{
		sf::SoundBuffer buffer;
	public:
		SoundEffect(const std::string& path)
		{
			// Load sound into buffer
			buffer.loadFromFile(get_res_folder_path(SOUND, path));
		}

		friend class AudioPlayer;
	};
}