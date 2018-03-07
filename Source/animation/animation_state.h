#pragma once
#include <memory>
#include <string>

#include "animation_clip.h"

class AnimationState
{
private:
	std::string name;
	std::shared_ptr<AnimationClip> clip;
	const std::string transition_state = "";

public:
	AnimationState(std::string name, std::shared_ptr<AnimationClip> clip, std::string transition_state = "");

	void update_clip(const float delta_millis);

	void reset();

	const std::shared_ptr<AnimationClip>& get_clip() const 
	{
		return clip;
	}

	std::string get_transition_state() const
	{
		return transition_state;
	}

	std::string get_name() const
	{
		return name;
	}
};