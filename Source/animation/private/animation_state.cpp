#include "animation/animation_state.h"

AnimationState::AnimationState(std::string name, std::shared_ptr<AnimationClip> clip, std::string transition_state)
	: name(name), clip(clip), transition_state(transition_state) {}

void AnimationState::update_clip(const float delta_millis)
{
	clip->update(delta_millis);
}

void AnimationState::reset()
{
	clip->reset();
}