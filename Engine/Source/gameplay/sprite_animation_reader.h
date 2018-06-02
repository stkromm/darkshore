#pragma once

#include "core/json/json.h"
#include "animation/animation_state_machine.h"
#include "sprite_animation_clip.h"

namespace ds {
	std::shared_ptr<AnimationStateMachine> read_sprite_animation_file(std::shared_ptr<scene::Sprite> sprite, json source);
}