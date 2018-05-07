#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "animation/animation_clip.h"
#include "tile_layer.h"

namespace tilemap
{
struct TileFrame
{
	uint32_t tile_index;
	float duration;
};

class TileAnimationClip : public AnimationClip
{
private:
	uint32_t frame_id = 0;
	uint32_t tile_id = 0;
	std::shared_ptr<tilemap::TileLayer> tile_map_layer;

protected:
	std::vector<TileFrame> frames{};

public:
	TileAnimationClip(const uint32_t tile_id, std::shared_ptr<tilemap::TileLayer> tile_map_layer, std::vector<TileFrame>& frames) : tile_id(tile_id),
		tile_map_layer(
			std::move(tile_map_layer)), frames(frames)
	{
		duration = 0;
		for (auto& frame : frames)
		{
			duration += frame.duration;
		}
		TileAnimationClip::reset();
	}

	void reset() override
	{
		remaining_clip_time = duration;
		frame_id = 0;
		on_frame_update(frame_id);
	}

	virtual void on_frame_update(const uint32_t frame_id)
	{
		if (frame_id != 0)
		{
			tile_map_layer->update_tile_state(tile_id, frames[frame_id - 1].tile_index);
		}
	}

	void update(const float delta_millis) override
	{
		remaining_clip_time -= delta_millis;
		float frame_end_time = 0;
		const float escaped_time = duration - remaining_clip_time;

		for (uint32_t i = 0; i < frames.size(); ++i)
		{
			TileFrame& frame = frames[i];
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
