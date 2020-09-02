#include "gui/text.h"
#include "platform/asset_manager.h"
#include "graphics/graphics.h"
#include "platform/window_manager.h"
#include "game/game.h"

namespace ds {
	namespace gui {
		Text::Text(std::string text)
		{
			this->text = text;
			this->dirty = true;
			font = std::make_unique<ds::fonts::Font>("font.ttf");
			shader_asset = AssetManager::load_asset<ShaderAsset>("text.shader");
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

		void Text::set_text(std::string text)
		{
			this->text = text;
			this->dirty = true;
		}

		std::string Text::get_render_text()
		{
			return this->text;
		}
		size_t counter = 10000000000000000000;
		bool Text::needs_rerender()
		{
			counter++;
			std::stringstream ss;
			ss << counter;
			this->set_text(ss.str());
			if (this->dirty) {
				generate_vertex_data();
				this->dirty = false;
			}
			this->vertex_array->bind();
			this->index_buffer->bind();

			this->vertex_array->bind();

			this->shader_asset->shader->bind();
			this->font->get_texture()->bind(0);
			this->shader_asset->shader->set_uniform_1i("tex", 0);
			const platform::Screen screen = platform::WindowManager::get_window().get_screen();
			const float width = screen.width;
			const float height = screen.height;
			auto transformation = Mat4x4(1).orthographic(-width / 2.f, width / 2.f, -height / 2.f, height / 2.f, -1, 1);
			auto screenToProj = Mat4x4(1);
			screenToProj.set_translation({ -width / 2.f + 16, height / 2.f - 8, 0 });
			screenToProj.scale(0.1, 0.1, 1);
			this->shader_asset->shader->set_uniform_mat4x4("pr_matrix", screenToProj * transformation);
			this->vertex_array->draw(*index_buffer);
			return false;
		};
		void Text::generate_vertex_data()
		{
			this->vertices.clear();
			std::shared_ptr<fonts::Font> font = this->font;

			const platform::Screen screen = platform::WindowManager::get_window().get_screen();
			float cursor_x = 0;
			float cursor_y = 0;
			const uint32 color = 0x0F0F0F + cursor_x;
			for (auto& character : this->text) {
				ds::fonts::Glyph glyph = font->get_glyph(character);
				if (character == ' ') {
					glyph.s0 = 0.0f;
					glyph.s1 = 0.0f;
					glyph.t0 = 0.0f;
					glyph.t1 = 0.0f;
				}
				const uint32 t_index = uint32(font->get_texture()->get_id());
				this->vertices.push_back({
					cursor_x + glyph.offset_x, cursor_y + glyph.offset_y - glyph.height,
					glyph.s0, glyph.t0,
					t_index,
					color
					});
				this->vertices.push_back({
					cursor_x + glyph.advance_x, cursor_y + glyph.offset_y - glyph.height,
					glyph.s1, glyph.t0,
					t_index,
					color
					});
				this->vertices.push_back({
					cursor_x + glyph.advance_x, cursor_y + glyph.offset_y,
					glyph.s1, glyph.t1,
					t_index,
					color
					});
				this->vertices.push_back({
					cursor_x + glyph.offset_x, cursor_y + glyph.offset_y,
					glyph.s0, glyph.t1,
					t_index,
					color
					});
				cursor_x += glyph.advance_x;
			}
			vertex_buffer->update(vertices.data(), sizeof(GlyphVertex) * (vertices.size()));

			const uint32 indices_size = vertices.size() / 4 * 6;
			this->index_buffer->set_count(indices_size);
		}
	};
};