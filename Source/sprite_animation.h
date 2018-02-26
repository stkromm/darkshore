#pragma once

#include <vector>
#include <memory>

#include "graphics/texture.h"

namespace graphics {
struct SpriteAnimationFrame {
	float duration;
	TexturePatch texture_patch;
};

class SpriteAnimation
{
private:
	std::shared_ptr<Texture> texture;
	std::vector<SpriteAnimationFrame> frames;
public:
	SpriteAnimation(std::shared_ptr<Texture> texture, std::vector<SpriteAnimationFrame>& frames);
	~SpriteAnimation();
};
}
