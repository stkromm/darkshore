#include <utility>
#include "graphics/sprite.h"
#include "platform/asset_manager.h"
#include "graphics/render_manager.h"

using namespace graphics;


Sprite::~Sprite()
{
	std::cout << "Delete sprite" << std::endl;
}

Sprite::Sprite(std::shared_ptr<Transform> transform, const math::Vec2 offset, const math::Vec2 size,
               TexturePatch& patch, const uint32_t color) :
	transform(std::move(transform)), color(color), texture(patch.texture), patch(patch)
{
}

void Sprite::change_patch(TexturePatch& patch)
{
	this->patch = patch;
}

void Sprite::draw(const float interpolation) const
{
	RenderManager::get_sprite_renderer()->submit(interpolation, get_texture_patch(), get_position(), get_extends(), color, transform);
}
