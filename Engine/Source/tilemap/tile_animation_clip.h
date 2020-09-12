#pragma once

#include <vector>

#include "graphics/tiled_texture.h"
#include "animation/animation_manager.h"

namespace ds {
	namespace tilemap {
		struct Frame
		{
			ds::graphics::TexturePatch patch;
			float duration;
		};

		class TileAnimationClip : public AnimationClip {
		public:
			std::vector<Frame> frames;
			uint_fast32_t frame_id = 0;
			ds::graphics::TexturePatch patch;

			TileAnimationClip(std::vector<Frame> frames) : frames(frames) {
				duration = 0;
				for (auto& frame : frames)
				{
					duration += frame.duration;
				}
				reset();
			}

			virtual void on_frame_update(const uint_fast32_t frame_id)
			{
				patch = frames[frame_id].patch;
			}

			void reset() override
			{
				remaining_clip_time = duration;
				frame_id = 0;
				on_frame_update(frame_id);
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
	}
}