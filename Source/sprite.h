#pragma once

#include <vector>

#include "math/vec2.h"
#include "graphics/scene.h"
#include "graphics/texture.h"
#include "transform.h"
#include "platform/asset.h"

namespace graphics {
	struct Vertex {
		float x;
		float y;
		float tc_x;
		float tc_y;
		unsigned int color;

		std::string to_string() const {
			std::stringstream sstream;
			sstream << "(" << x << "," << y << "," << tc_x << "," << tc_y << "," << color << ")";
			return sstream.str();
		}
	};

	class Sprite : public Renderable
	{
	private:
		Vertex vertices[4];

		unsigned int indices[6] = {
			0,1,2,
			2,3,0
		};

		std::shared_ptr<Transform> transform;
		math::Vec2 extends;

		std::shared_ptr<graphics::Texture> texture;
		graphics::TexturePatch& patch;

		std::shared_ptr<Shader> shader;
		std::unique_ptr<VertexBuffer> vertex_buffer;
		std::unique_ptr<VertexArray> vertex_array;
		std::unique_ptr<IndexBuffer> index_buffer;
	public:
		~Sprite()
		{
			std::cout << "Delete sprite" << std::endl;
		}
		Sprite(std::shared_ptr<Transform> transform, math::Vec2 offset, math::Vec2 size, graphics::TexturePatch& patch, unsigned int color = 0x000000FF) :
			transform(transform), texture(patch.texture), patch(patch)
		{
			vertices[0] =
			{
				0 + offset.x, 0 + offset.y,
				patch.x1, patch.y1,
				color
			};
			vertices[1] =
			{
				size.x + offset.x, 0 + offset.y,
				patch.x2, patch.y1,
				color
			};
			vertices[2] =
			{
				size.x + offset.x, size.y + offset.y,
				patch.x2, patch.y2,
				color
			};
			vertices[3] =
			{
				0 + offset.x, size.y + offset.y,
				patch.x1, patch.y2,
				color
			};

			vertex_array = std::make_unique<VertexArray>();
			vertex_buffer = std::make_unique<VertexBuffer>(vertices, sizeof(Vertex) * 4);
			index_buffer = std::make_unique<IndexBuffer>(indices, 6);

			VertexBufferLayout vb_layout;
			vb_layout.push<float>(2);
			vb_layout.push<float>(2);
			vb_layout.push<unsigned int>(1);
			vertex_array->add_buffer(*vertex_buffer, vb_layout);

			shader = AssetManager::load_asset<Shader>("basic.shader");

			for (int i = 0; i < 4; i++)
			{
				std::cout << "Vertex " << i << " " << vertices[i].to_string() << std::endl;
			}
		}

		void draw(Renderer& renderer) const override
		{
			shader->bind();
			shader->set_uniform_mat4x4("pr_matrix", graphics::SceneManager::get_scene()->get_camera()->get_projection());
			shader->set_uniform_mat4x4("vw_matrix", transform->get_local_to_world());
			texture->bind();
			shader->set_uniform_1i("tex", 0);
			renderer.draw(*vertex_array, *index_buffer, *shader);
		}
	};
}

