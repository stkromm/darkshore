#include <utility>
#include "scene/standalone_sprite.h"
#include "scene/sprite_vertex.h"
#include "platform/asset_manager.h"
#include "core/logger/log.h"
#include "scene/scene_manager.h"
#include "scene/render_manager.h"
#include "scene/shader_asset.h"

using namespace graphics;


StandaloneSprite::~StandaloneSprite()
{
	LOG_INFO << "Delete standalone sprite" << LOG_END;
}

StandaloneSprite::StandaloneSprite(std::shared_ptr<Transform> transform, const math::FVec2 offset, const math::FVec2 size,
                                   ds::graphics::TexturePatch& patch, const uint32_t color) : Sprite(transform, offset, size, patch, color)
	
{
	vertices[0] =
	{
		0 + offset.x, 0 + offset.y,
		patch.x1, patch.y1,  0,
		color
	};
	vertices[1] =
	{
		size.x + offset.x, 0 + offset.y,
		patch.x2, patch.y1, 0,
		color
	};
	vertices[2] =
	{
		size.x + offset.x, size.y + offset.y,
		patch.x2, patch.y2, 0,
		color
	};
	vertices[3] =
	{
		0 + offset.x, size.y + offset.y,
		patch.x1, patch.y2, 0,
		color
	};

	vertex_array = std::make_unique<ds::graphics::VertexArray>();
	vertex_buffer = std::make_unique<ds::graphics::VertexBuffer>(vertices, sizeof(Vertex) * 4);
	index_buffer = std::make_unique<ds::graphics::IndexBuffer>(indices, 6);

	ds::graphics::VertexBufferLayout vb_layout;
	vb_layout.push<float>(2);
	vb_layout.push<float>(2);
	vb_layout.push<uint32_t>(1);
	vb_layout.push<unsigned char>(4);
	vertex_array->add_buffer(*vertex_buffer, vb_layout);

	shader_asset = AssetManager::load_asset<ShaderAsset>("basic.shader");
	shader = shader_asset->shader;
}

void StandaloneSprite::change_patch(ds::graphics::TexturePatch& patch)
{
	vertices[0].tc_x = patch.x1;
	vertices[0].tc_y = patch.y1;
	vertices[1].tc_x = patch.x2;
	vertices[1].tc_y = patch.y1;
	vertices[2].tc_x = patch.x2;
	vertices[2].tc_y = patch.y2;
	vertices[3].tc_x = patch.x1;
	vertices[3].tc_y = patch.y2;

	vertex_array->bind();
	vertex_buffer->update(vertices, sizeof(Vertex) * 4);
}

void StandaloneSprite::draw(const float interpolation) const
{
	shader->bind();
	shader->set_uniform_mat4x4("pr_matrix", SceneManager::get_scene()->get_camera()->get_projection());
	shader->set_uniform_mat4x4("vw_matrix", transform->get_local_to_world());

	texture->bind();
	shader->set_uniform_1i("tex", 0);
	RenderManager::get_scene_renderer()->draw(*vertex_array, *index_buffer, *shader);
}
