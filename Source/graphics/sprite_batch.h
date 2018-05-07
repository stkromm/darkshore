#pragma once

#include <vector>
#include <memory>
#include "vertex_buffer.h"
#include "vertex_array.h"
#include "index_buffer.h"
#include "scene_renderer.h"
#include "texture.h"
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

		std::unique_ptr<VertexBuffer> vertex_buffer;
		std::unique_ptr<VertexArray> vertex_array;
		std::unique_ptr<IndexBuffer> index_buffer;
		std::shared_ptr<SceneRenderer> renderer;
		std::shared_ptr<Shader> shader;

	public:
		DynamicSpriteBatch(const std::shared_ptr<SceneRenderer> renderer, const std::shared_ptr<Shader> shader) : renderer(renderer), shader(shader)
		{
			vertex_array = std::make_unique<VertexArray>();
			vertex_buffer = std::make_unique<VertexBuffer>(vertices.data(), 0);
			index_buffer = std::make_unique<IndexBuffer>(indices.data(), 0);

			VertexBufferLayout layout;
			layout.push<float>(2);
			layout.push<float>(2);
			layout.push<uint32_t>(1);
			layout.push<unsigned char>(4);

			vertex_array->add_buffer(*vertex_buffer, layout);
		}

		void prepare(const math::Mat4x4 projection)
		{
			shader->bind();
			shader->set_uniform_mat4x4("pr_matrix", projection);
			shader->set_uniform_mat4x4("vw_matrix", math::Mat4x4(1.f));
			shader->set_uniform_1i("tex", 0);
		}

		void submit(const float interpolation, const TexturePatch texture_patch, const math::FVec2 position, const math::FVec2 extends, const uint32_t color, const std::shared_ptr<Transform> transform)
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
					std::cout << "Flush because tex" << std::endl;
					flush();
				}
				texture_ids.push_back(texture_id);
				texture_index = texture_ids.size() - 1;

				texture_patch.texture->bind(texture_index); 
				shader->set_uniform_1i("tex", texture_index);
			}

			const auto local_to_world = transform->get_local_to_world();
			const auto world_position = position + math::FVec2{ local_to_world[12], local_to_world[13] };
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

			indices.push_back(vertices.size() + 0);
			indices.push_back(vertices.size() + 1);
			indices.push_back(vertices.size() + 2);
			indices.push_back(vertices.size() + 2);
			indices.push_back(vertices.size() + 3);
			indices.push_back(vertices.size() + 0);

			vertices.push_back(a);
			vertices.push_back(b);
			vertices.push_back(c);
			vertices.push_back(d);

			
			if (vertices.size() >= 1024)
				flush();
		}

		void flush()
		{
			vertex_array->bind();

			vertex_buffer->update(vertices.data(), sizeof(Vertex) * (vertices.size() ));
			index_buffer->update(indices);

			renderer->draw(*vertex_array, *index_buffer, *shader);

			vertices.clear();
			indices.clear();
			texture_ids.clear();
		}
	};
}
