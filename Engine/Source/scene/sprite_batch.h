#pragma once

#include <vector>
#include <memory>
#include "core/logger/log.h"
#include "graphics/vertex_buffer.h"
#include "graphics/vertex_array.h"
#include "graphics/index_buffer.h"
#include "graphics/renderer.h"
#include "graphics/texture.h"
#include "core/transform.h"
#include "sprite_vertex.h"
#include "scene.h"

namespace graphics
{

	class DynamicSpriteBatch
	{
	private:
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		std::vector<uint32_t> texture_ids;

		std::unique_ptr<ds::graphics::VertexBuffer> vertex_buffer;
		std::unique_ptr<ds::graphics::VertexArray> vertex_array;
		std::unique_ptr<ds::graphics::IndexBuffer> index_buffer;
		std::shared_ptr<ds::graphics::SceneRenderer> renderer;
		std::shared_ptr<ds::graphics::Shader> shader;

	public:
		DynamicSpriteBatch(const std::shared_ptr<ds::graphics::SceneRenderer> renderer, const std::shared_ptr<ds::graphics::Shader> shader) : renderer(renderer), shader(shader)
		{
			vertex_array = std::make_unique<ds::graphics::VertexArray>();

			vertex_buffer = std::make_unique<ds::graphics::VertexBuffer>(vertices.data(), 0);
			indices.resize(1024 * 6);
			for (int i = 0; i < 1024; ++i)
			{
				const uint32 index = i * 6;
				const uint32 v_index = i * 4;
				indices[index] = v_index;
				indices[index + 1] = v_index + 1;
				indices[index + 2] = v_index + 2;
				indices[index + 3] = v_index + 2;
				indices[index + 4] = v_index + 3;
				indices[index + 5] = v_index;
			}
			index_buffer = std::make_unique<ds::graphics::IndexBuffer>(indices.data(), indices.size());

			ds::graphics::VertexBufferLayout layout;
			layout.push<float>(2);
			layout.push<float>(2);
			layout.push<uint32_t>(1);
			layout.push<unsigned char>(4);

			vertex_array->add_buffer(*vertex_buffer, layout);
		}

		void prepare()
		{
		}

		std::shared_ptr<ds::graphics::Shader> get_shader() const
		{
			return shader;
		}

		void submit(const float interpolation, const ds::graphics::TexturePatch& texture_patch, const math::FVec2 position, const math::FVec2 extends, const uint32_t color)
		{
			// Enable texture
			const uint32_t texture_id = texture_patch.texture->get_id();
			int texture_index = -1;
			for (uint32_t i = 0; i < texture_ids.size(); ++i)
			{
				if (texture_ids[i] == texture_id)
				{
					texture_index = i;
					break;
				}
			}
			if (texture_index == -1)
			{
				if (texture_ids.size() == 8)
				{
					LOG_INFO << "Flush because too many textures active" << LOG_END;
					flush();
				}
				texture_ids.push_back(texture_id);
				texture_index = texture_ids.size() - 1;

				texture_patch.texture->bind(texture_index);
				shader->set_uniform_1i("tex", texture_index);
			}

			const auto world_position = position;
			const auto world_extends = extends;

			const uint32 t_index = uint32(texture_index);
			vertices.push_back({
				world_position.x, world_position.y,
				texture_patch.x1, texture_patch.y1,
				t_index,
				color
				});
			vertices.push_back({
				world_position.x + world_extends.x, world_position.y,
				texture_patch.x2, texture_patch.y1,
				t_index,
				color
				});
			vertices.push_back({
				world_position.x + world_extends.x, world_position.y + world_extends.y,
				texture_patch.x2, texture_patch.y2,
				t_index,
				color
				});
			vertices.push_back({
				world_position.x, world_position.y + world_extends.y,
				texture_patch.x1, texture_patch.y2,
				t_index,
				color
				});


			//if (vertices.size() >= 1024)
			//	flush();
		}

		void flush()
		{
			vertex_array->bind();
			vertex_buffer->update(vertices.data(), sizeof(Vertex) * (vertices.size()));

			const uint32 indices_size = vertices.size() / 4 * 6;
			index_buffer->set_count(indices_size);

			renderer->draw(*vertex_array, *index_buffer, *shader);

			vertices.clear();
			texture_ids.clear();
		}
	};
}
