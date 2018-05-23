#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "graphics/texture.h"
#include "scene/sprite.h"
#include "animation/animation_clip.h"

struct Frame
{
	ds::graphics::TexturePatch patch;
	float duration;
};

class SpriteAnimationClip : public AnimationClip
{
private:
	uint_fast32_t frame_id = 0;
	std::shared_ptr<graphics::Sprite> sprite;
protected:
	std::vector<Frame> frames;
public:

	SpriteAnimationClip(std::shared_ptr<graphics::Sprite> sprite, std::vector<Frame>& frames) : sprite(std::move(sprite)),
	                                                                                            frames(frames)
	{
		duration = 0;
		for (auto& frame : frames)
		{
			duration += frame.duration;
		}
		SpriteAnimationClip::reset();
	}

	void reset() override
	{
		remaining_clip_time = duration;
		frame_id = 0;
		on_frame_update(frame_id);
	}

	virtual void on_frame_update(const uint_fast32_t frame_id)
	{
		sprite->change_patch(frames[frame_id].patch);
	}

	void update(const float delta_millis) override
	{
		remaining_clip_time -= delta_millis;
		float frame_end_time = 0;
		const float escaped_time = duration - remaining_clip_time;

		for (uint_fast32_t i = 0; i < frames.size(); ++i)
		{
			Frame& frame = frames[i];
			frame_end_time += frame.duration;
			if (frame_end_time > escaped_time)
			{
				if (i != frame_id)
				{
					frame_id = i;
					on_frame_update(frame_id);
				}
				return;
			}
		}
		frame_id = 0;
		on_frame_update(frame_id);
	}
};
