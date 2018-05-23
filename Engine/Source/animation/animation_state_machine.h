#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "animation/animation_state.h"

class AnimationStateMachine
{
private:
	std::string pending_transisitons = "";
	std::string current_state_name;
	std::unordered_map<std::string, std::unique_ptr<AnimationState>> states;

protected:
	AnimationState * get_state();

public:
	void add_state(AnimationState state);
	void tick(float delta_millis);
	void transition(const std::string& state_name, bool force = true)
	{
		if (!force)
			pending_transisitons = state_name;
		else
		{
			if (current_state_name != state_name)
			{
				pending_transisitons = state_name;
				current_state_name = state_name;
			}
			else
			{
				pending_transisitons = state_name;
			}
		}
	}

	std::string get_current_state()
	{
		return current_state_name;
	}
};
