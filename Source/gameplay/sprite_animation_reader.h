#pragma once

#include "json.h"
#include "animation/animation_state_machine.h"
#include "sprite_animation_clip.h"

std::shared_ptr<AnimationStateMachine> read_sprite_animation_file(std::shared_ptr<graphics::Sprite> sprite, json source);
