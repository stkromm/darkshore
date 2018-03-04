#include "music.h"

sf::Music* music;

void audio::play_background_music(std::string path)
{
	if (!music) music = new sf::Music();
	music->stop();
	//InputStream input_stream = InputStream(ResourceHandle(get_res_folder_path(ResourceType::SOUND, path)));
	//music->openFromStream(input_stream);
	music->openFromFile(get_res_folder_path(AssetType::SOUND, path));
	music->play();
}
