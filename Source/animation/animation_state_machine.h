#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "graphics/renderable.h"
#include "graphics/texture.h"
#include "sprite.h"

struct Frame
{
	graphics::TexturePatch patch;
	float duration;
};

class AnimationClip : public graphics::Renderable
{
	int frame_id = 0;
	std::vector<Frame> frames;
	std::shared_ptr<graphics::Sprite> sprite;
public:
	float remaining_clip_time;
	float duration;

	AnimationClip(std::shared_ptr<graphics::Sprite> sprite, std::vector<Frame>& frames) : frames(frames), sprite(sprite)
	{
		duration = 0;
		for (auto& frame : frames)
		{
			duration += frame.duration;
		}
		reset();
	}

	void reset()
	{
		remaining_clip_time = duration;
		frame_id = 0;
		sprite->change_patch(frames[frame_id].patch);
	}

	void update()
	{
		float frame_end_time = 0;
		float escaped_time = duration - remaining_clip_time;

		for (int i = 0; i < frames.size(); ++i)
		{
			Frame& frame = frames[i];
			frame_end_time += frame.duration;
			if (frame_end_time > escaped_time)
			{
				if (i != frame_id)
				{
					frame_id = i;
					sprite->change_patch(frames[frame_id].patch);
				}
				return;
			}
		}
		frame_id = 0;
		sprite->change_patch(frames[frame_id].patch);
	}
};

struct AnimationState
{
	std::string name;
	std::shared_ptr<AnimationClip> clip;
	std::string transition_state = "";

	void update_clip(float delta_millis)
	{
		clip->remaining_clip_time -= delta_millis;
		clip->update();
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

public:
	void add_state(AnimationState state)
	{
		states[state.name] = std::make_unique<AnimationState>(state);
	}

	AnimationState* get_state()
	{
		auto& current_state_search = states.find(current_state_name);
		AnimationState* current_state;
		if (current_state_search == states.end())
		{
			current_state_name = states.begin()->first;
			current_state = states.begin()->second.get();
		}
		else
		{
			current_state = current_state_search->second.get();
		}
		return current_state;
	}

	void tick(float delta_millis)
	{
		AnimationState* current_state = get_state();

		float remaining_time = current_state->clip->remaining_clip_time - delta_millis;
		if (remaining_time <= 0.f)
		{
			auto& transition_state = states.find(current_state->transition_state);
			if (transition_state != states.end())
			{
				current_state_name = transition_state->first;
				transition_state->second->reset();
			}
			else
			{
				current_state->reset();
			}

			tick(remaining_time);
		}
		else
		{
			current_state->update_clip(delta_millis);
		}
	}
};