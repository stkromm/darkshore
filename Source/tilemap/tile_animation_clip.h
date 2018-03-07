#pragma once

#include <memory>
#include <vector>

#include "tilemap/tile.h"
#include "animation/animation_clip.h"

struct Frame
{
	uint32_t tile_index;
	float duration;
};

class TileAnimationClip : public AnimationClip
{
private:
	int frame_id = 0;
	std::shared_ptr<Tile> tile_map_layer;
protected:
	std::vector<Frame> frames;
public:

	TileAnimationClip(std::shared_ptr<Tile> tile_map_layer, std::vector<Frame>& frames) : frames(frames), tile_map_layer(tile_map_layer)
	{
		duration = 0;
		for (auto& frame : frames)
		{
			duration += frame.duration;
		}
		reset();
	}

	void reset() override
	{
		remaining_clip_time = duration;
		frame_id = 0;
		on_frame_update(frame_id);
	}

	virtual void on_frame_update(uint32_t frame_id)
	{
		if (frame_id != 0) {
			//tile_map_layer->update_tiles(frames[frame_id - 1].tile_index, frames[frame_id].tile_index)
		}
	}

	void update(float delta_millis) override
	{
		remaining_clip_time -= delta_millis;
		float frame_end_time = 0;
		float escaped_time = duration - remaining_clip_time;

		for (uint32_t i = 0; i < frames.size(); ++i)
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