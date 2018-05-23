#pragma once

class AnimationClip
{
public:
	virtual ~AnimationClip() = default;
	float remaining_clip_time = 0.f;
	float duration = 0.f;

	virtual void reset() = 0;
	virtual void update(float delta_millis) = 0;
};
