#include <utility>
#include "graphics/sprite.h"
#include "core/platform/asset_manager.h"
#include "graphics/render_manager.h"
#include "core/logger/log.h"
using namespace graphics;


Sprite::~Sprite()
{
	LOG_INFO << "Delete sprite" << LOG_END;
}

Sprite::Sprite(std::shared_ptr<Transform> transform, const math::FVec2 offset, const math::FVec2 size,
               TexturePatch& patch, const uint32_t color) :
	patch(patch), transform(transform), color(color), texture(patch.texture), extends(size)
{
}

void Sprite::change_patch(TexturePatch& patch)
{
	this->patch = patch;
}

void Sprite::draw(const float interpolation) const
{
	RenderManager::get_sprite_renderer()->submit(interpolation, patch, get_position(), get_extends(), color, transform);
}
