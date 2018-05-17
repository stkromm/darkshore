#include <utility>
#include "graphics/standalone_sprite.h"
#include "graphics/sprite_vertex.h"
#include "core/platform/asset_manager.h"
#include "core/logger/log.h"
#include "graphics/scene_manager.h"
#include "graphics/render_manager.h"

using namespace graphics;


StandaloneSprite::~StandaloneSprite()
{
	LOG_INFO << "Delete standalone sprite" << LOG_END;
}

StandaloneSprite::StandaloneSprite(std::shared_ptr<Transform> transform, const math::FVec2 offset, const math::FVec2 size,
	TexturePatch& patch, const uint32_t color) : Sprite(transform, offset, size, patch, color)
	
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

	vertex_array = std::make_unique<VertexArray>();
	vertex_buffer = std::make_unique<VertexBuffer>(vertices, sizeof(Vertex) * 4);
	index_buffer = std::make_unique<IndexBuffer>(indices, 6);

	VertexBufferLayout vb_layout;
	vb_layout.push<float>(2);
	vb_layout.push<float>(2);
	vb_layout.push<uint32_t>(1);
	vb_layout.push<unsigned char>(4);
	vertex_array->add_buffer(*vertex_buffer, vb_layout);

	shader = AssetManager::load_asset<Shader>("basic.shader");
}

void StandaloneSprite::change_patch(TexturePatch& patch)
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
