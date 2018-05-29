#pragma once

#include "core/math/vec2.h"
#include <memory>

#include "audio/private/input_stream.h"
#include "sound_effect.h"

namespace audio
{

	class AudioPlayer
	{
		sf::Sound sound;
		math::FVec2 position;
		std::shared_ptr<SoundEffect> sound_effect;
	public:
		void set_sound_effect(std::shared_ptr<SoundEffect> effect)
		{
			this->sound_effect = effect;
			sound.setBuffer(sound_effect->buffer);
		}

		void apply()
		{
			sound.setBuffer(sound_effect->buffer);
			sound.setRelativeToListener(false);
			sound.setPosition(position.x, position.y, 0);
			sound.setMinDistance(10.f);
		}

		void trigger()
		{
			sound.play();
		}

		void stop();
		void pause();
		void resume();

	};
}
