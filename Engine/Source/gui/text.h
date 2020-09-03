#include <string>
#include "gui/gui.h"
#include "fonts/font.h"
#include "graphics/shader.h"
#include "graphics/vertex_buffer.h"
#include "graphics/vertex_array.h"
#include "graphics/index_buffer.h"

#include "scene/shader_asset.h"

namespace ds {
	namespace gui {
		struct GlyphVertex
		{
			float x;
			float y;
			float tc_x;
			float tc_y;
			uint32_t texture_id;
			uint32_t tint;

			std::string to_string() const
			{
				std::stringstream sstream;
				sstream << "(" << x << "," << y << "," << tc_x << "," << tc_y << "," << tint << ")";
				return sstream.str();
			}
		};

		class Text : GuiElement {
			std::string text;
			std::shared_ptr<fonts::Font> font;
			std::shared_ptr<ShaderAsset> shader_asset;

			std::unique_ptr<ds::graphics::VertexBuffer> vertex_buffer;
			std::unique_ptr<ds::graphics::VertexArray> vertex_array;
			std::unique_ptr<ds::graphics::IndexBuffer> index_buffer;

			std::vector<GlyphVertex> vertices;
			std::vector<uint32_t> indices;
			std::vector<uint32_t> texture_ids;

			void generate_vertex_data();
		public:
			Text(std::string text);
			virtual bool needs_rerender() override;
			void set_text(std::string text);
			std::string get_render_text() const;
			std::vector<GlyphVertex> get_vertex_data() const;
			Mat4x4 get_transformation() const;
			std::shared_ptr<graphics::Texture> get_texture() const;
		};
	}
}