#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "animation/animation_state.h"

class AnimationStateMachine
{
private:
	std::vector<std::string> pending_transisitons;
	std::string current_state_name;
	std::unordered_map<std::string, std::unique_ptr<AnimationState>> states;

protected:
	AnimationState * get_state();

public:
	void add_state(AnimationState state);
	void tick(const float delta_millis);
};