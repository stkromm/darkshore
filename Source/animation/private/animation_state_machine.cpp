#include "animation/animation_state_machine.h"
#include <iostream>

void AnimationStateMachine::add_state(AnimationState state)
{
	const auto& name = state.get_name();
	states[name] = std::make_unique<AnimationState>(std::move(state));
}

AnimationState* AnimationStateMachine::get_state()
{
	const auto current_state_search = states.find(current_state_name);
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

void AnimationStateMachine::tick(const float delta_millis)
{
	AnimationState* current_state = get_state();

	const float remaining_time = current_state->get_clip()->remaining_clip_time - delta_millis;
	if (remaining_time <= 0.f)
	{
		std::string transition_state_name = current_state->get_transition_state();

		if (!pending_transisitons.empty())
		{
			transition_state_name = pending_transisitons;
			pending_transisitons = "";
		}

		const auto transition_state = states.find(transition_state_name);

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
