#include "audio/music.h"

sf::Music* music;

void audio::play_background_music(std::string path)
{
	if (!music) music = new sf::Music();
	music->stop();
#ifdef DEVELOPMENT
	music->openFromFile(get_res_folder_path(AssetType::SOUND, path));
#else
	//InputStream input_stream = InputStream(ResourceHandle(get_res_folder_path(ResourceType::SOUND, path)));
	//music->openFromStream(input_stream);
#endif
	music->play();
}
