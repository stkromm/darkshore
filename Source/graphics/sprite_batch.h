#pragma once

#include <vector>
#include <memory>
#include "vertex_buffer.h"
#include "vertex_array.h"
#include "index_buffer.h"
#include "renderer.h"
#include "texture.h"
#include "core/transform.h"
#include "sprite_vertex.h"

namespace graphics
{

	class DynamicSpriteBatch 
	{
	private:
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		std::vector<uint32_t> texture_ids;

		std::unique_ptr<VertexBuffer> vertex_buffer;
		std::unique_ptr<VertexArray> vertex_array;
		std::unique_ptr<IndexBuffer> index_buffer;
		std::shared_ptr<SceneRenderer> renderer;
		std::shared_ptr<Shader> shader;
		math::Mat4x4 projection = math::Mat4x4(1.f);

	public:
		DynamicSpriteBatch(std::shared_ptr<SceneRenderer> renderer, std::shared_ptr<Shader> shader) : renderer(renderer), shader(shader)
		{
			vertex_array = std::make_unique<VertexArray>();
			vertex_buffer = std::make_unique<VertexBuffer>(vertices.data(), sizeof(Vertex) * 4);
			index_buffer = std::make_unique<IndexBuffer>(indices.data(), 6);

			VertexBufferLayout layout;
			layout.push<float>(2);
			layout.push<float>(2);
			layout.push<uint32_t>(1);
			layout.push<uint32_t>(1);

			vertex_array->add_buffer(*vertex_buffer, layout);
		}

		void prepare(math::Mat4x4 projection)
		{
			shader->bind();
			this->projection = projection;
		}

		void submit(const float interpolation, TexturePatch& texture_patch, math::Vec2 position, math::Vec2 extends, uint32_t color, std::shared_ptr<Transform> transform)
		{
			// Enable texture
			const uint32_t texture_id = texture_patch.texture->get_id();
			int texture_index = -1;
			for(uint32_t i = 0; i < texture_ids.size(); ++i)
			{
				if(texture_ids[i] == texture_id)
				{
					texture_index = i;
					break;
				}
			}
			if(texture_index == -1)
			{
				if(texture_ids.size() == 8)
				{
					flush();
				}
				texture_ids.push_back(texture_id);
				texture_index = texture_ids.size() - 1;
				texture_patch.texture->bind(texture_ids.size() - 1); 
				shader->set_uniform_1i("tex", texture_ids.size() - 1);
			}

			const auto world_position = position - transform->get_position();
			const auto world_extends = extends;

			const Vertex a = {
				world_position.x, world_position.y,
				texture_patch.x1, texture_patch.y1,
				texture_id,
				color
			};
			const Vertex b = {
				world_position.x + world_extends.x, world_position.y,
				texture_patch.x2, texture_patch.y1,
				texture_id,
				color
			};
			const Vertex c = {
				world_position.x + world_extends.x, world_position.y + world_extends.y,
				texture_patch.x2, texture_patch.y2,
				texture_id,
				color
			};
			const Vertex d = {
				world_position.x, world_position.y + world_extends.y,
				texture_patch.x1, texture_patch.y2,
				texture_id,
				color
			};

			vertices.push_back(a);
			vertices.push_back(b);
			vertices.push_back(c);
			vertices.push_back(d);

			indices.push_back(vertices.size() + 0);
			indices.push_back(vertices.size() + 1);
			indices.push_back(vertices.size() + 2);
			indices.push_back(vertices.size() + 2);
			indices.push_back(vertices.size() + 3);
			indices.push_back(vertices.size() + 0);
			
			if (vertices.size() >= 1024)
				flush();
		}

		void flush()
		{
			shader->bind();

			shader->set_uniform_mat4x4("pr_matrix", projection);
			shader->set_uniform_mat4x4("vw_matrix", math::Mat4x4(1.f));
			vertex_array->bind();
			vertex_buffer->update(vertices.data(), sizeof(Vertex) * vertices.size());
			index_buffer->update(indices);
			renderer->draw(*vertex_array, *index_buffer, *shader);
			vertices.clear();
			texture_ids.clear();
		}
	};
}
