#include "audio/music.h"

#include "audio/private/input_stream.h"

namespace ds
{
	namespace audio
	{
		namespace BackgroundMusic
		{
			sf::Music* music;

			void play(const std::string& path, float fade_in)
			{
				if (!music) music = new sf::Music();
				music->stop();
#ifdef DEVELOPMENT
				music->openFromFile(get_res_folder_path(SOUND, path));
#else
				//InputStream input_stream = InputStream(ResourceHandle(get_res_folder_path(ResourceType::SOUND, path)));
				//music->openFromStream(input_stream);
#endif
			}

			void set_volume(const float volume)
			{
				if(music)
				{
					music->setVolume(volume);
				}
			}

			void resume(const float fade_in)
			{
				if(music)
				{
					music->play();
				}
			}

			void pause(const float fade_out)
			{
				if(music)
				{
					music->pause();
				}
			}

			void stop(const float fade_out)
			{
				if(music)
				{
					music->stop();
				}
			}
		}
	}
}
