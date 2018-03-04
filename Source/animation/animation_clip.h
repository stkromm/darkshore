#pragma once

class AnimationClip
{
public:
	float remaining_clip_time;
	float duration;

	virtual void reset() = 0;

	virtual void update(float delta_millis) = 0;
};