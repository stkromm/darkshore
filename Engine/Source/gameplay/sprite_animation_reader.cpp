#include "sprite_animation_reader.h"

#include "core/json/json.h"
#include "animation/animation_state_machine.h"
#include "graphics/texture.h"
#include "sprite_animation_clip.h"
#include "graphics/tiled_texture.h"
#include "platform/asset_manager.h"
#include "scene/texture_asset.h"

using namespace ds;

std::shared_ptr<AnimationStateMachine> ds::read_sprite_animation_file(std::shared_ptr<scene::Sprite> sprite, json source)
{
	const std::string texture_name = source["texture"];
	const ds::graphics::TiledTexture tiled_texture = ds::graphics::TiledTexture(AssetManager::load_asset<TextureAsset>(texture_name)->texture, source["tile_width"], source["tile_height"]);
	std::shared_ptr<AnimationStateMachine> animation_state_machine = std::make_shared<AnimationStateMachine>();

	for (auto& clip : source["clips"])
	{
		std::vector<Frame> frames;
		for (auto& frame : clip["frames"])
		{
			frames.push_back({ tiled_texture[frame["x"]][frame["y"]], frame["duration"] });
		}
		std::string transition;
		if (clip["transition"].is_string())
		{
			animation_state_machine->add_state({ clip["name"], std::make_shared<SpriteAnimationClip>(
				sprite, frames), clip["transition"] });
		}
		else
		{
			animation_state_machine->add_state({ clip["name"], std::make_shared<SpriteAnimationClip>(
				sprite, frames) });
		}
		std::cout << clip["name"] << std::endl;
	}

	return animation_state_machine;
}
