#pragma once

#include <string>
#include <utility>

#include "core/math/vec2.h"
#include "graphics/texture.h"


namespace graphics
{
	namespace ftgl {
		struct texture_atlas_t;
		struct texture_font_t;
	}
	class Font
	{
	private:
		ftgl::texture_atlas_t* m_FTAtlas;
		ftgl::texture_font_t* m_FTFont;
		std::string name;
		std::shared_ptr<Texture> texture;
		float size;
		math::Vec2 scale;
	public:
		Font(std::string name, const std::string& file_path, float size);

		void set_scale(float x, float y);
		math::Vec2 get_scale() const;
		std::string get_name() const;
		float get_size() const;
		void set_size(float size);

		float get_width(std::string text) const;
		float get_height(std::string text) const;
		math::Vec2 get_size(std::string text) const;
		std::shared_ptr<Texture> get_texture() const;
	private:
		void update_atlas() const;
	};

}