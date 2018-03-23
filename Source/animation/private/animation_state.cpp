#include <utility>
#include "animation/animation_state.h"

AnimationState::AnimationState(std::string name, std::shared_ptr<AnimationClip> clip, std::string transition_state)
	: name(std::move(name)), clip(std::move(clip)), transition_state(std::move(transition_state))
{
}

void AnimationState::update_clip(const float delta_millis) const
{
	clip->update(delta_millis);
}

void AnimationState::reset() const
{
	clip->reset();
}
