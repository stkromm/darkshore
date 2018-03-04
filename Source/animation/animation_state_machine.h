#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "animation_clip.h"

struct AnimationState
{
	const std::string name;
	std::shared_ptr<AnimationClip> clip;
	const std::string transition_state = "";

	void update_clip(const float delta_millis)
	{
		clip->update(delta_millis);
	}

	void reset()
	{
		clip->reset();
	}
};

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