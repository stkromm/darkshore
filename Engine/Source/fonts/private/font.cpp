#include "fonts/font.h"

#include "third_party/freetype/ftglyph.h"
#include "platform/resource_handle.h"

const float SUBPIXEL_2_PIXEL = 1 / 64.0f;
const uint32 TEXTURE_SIZE = 1024;
namespace ds {
	namespace fonts {

		Font::Font(const std::string path) {
			if (FT_Init_FreeType(&library))
				throw std::runtime_error("FT_Init_FreeType failed");
			if (FT_New_Face(library, get_res_folder_path(FONT, path).c_str(), 0, &this->face))
				throw std::runtime_error("FT_New_Face failed (there is probably a problem with your font file)");
			this->texture_atlas = std::make_unique<ds::graphics::TextureAtlas>(TEXTURE_SIZE, TEXTURE_SIZE, 4);
		}
		Font::~Font() {
			FT_Done_Face(face);
			FT_Done_FreeType(library);
		}

		std::shared_ptr<graphics::Texture> Font::get_texture() {
			return this->texture_atlas->get_texture();
		}

		Glyph Font::get_glyph(const char character) {
			auto cached_glyph = this->glyph_cache.find(character);
			if (cached_glyph != this->glyph_cache.end()) {
				return cached_glyph->second;
			}
			FT_Set_Char_Size(face, 0, 72 << 6, 72, 72);

			auto glyph_index = FT_Get_Char_Index(this->face, character);
			if (FT_Load_Glyph(this->face, glyph_index, FT_LOAD_DEFAULT))
				throw std::runtime_error("FT_Load_Glyph failed");

			Glyph glyph;
			glyph.codepoint = character;
			FT_Glyph ft_glyph;
			auto glyph_error = FT_Get_Glyph(this->face->glyph, &ft_glyph);
			if (glyph_error)
				throw std::runtime_error("FT_Get_Glyph failed" + glyph_error);
			FT_Glyph_To_Bitmap(&ft_glyph, ft_render_mode_normal, 0, 1);
			FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)ft_glyph;

			FT_Bitmap& bitmap = bitmap_glyph->bitmap;
			int character_width = bitmap.width;
			int character_height = bitmap.rows;
			// Create texture data
			{
				// Allocate Memory For The Texture Data.
				// TODO: Out of memory exception here
				// TODO: Use 8bit color channel instead of redundant 24bit
				auto expanded_data = new int[character_width * character_height];
				for (uint32 j = 0; j < character_height; j++) {
					for (uint32 i = 0; i < character_width; i++) {
						auto bitmapValue = (i >= bitmap.width || j >= bitmap.rows) ? 0 : (bitmap.buffer[i + bitmap.width*j]);
						expanded_data[(i + j * character_width)] = (bitmapValue << 8) | (bitmapValue << 16) | (bitmapValue << 24) | 0xFF;
					}
				}
				// TODO: Handle texture atlas texture is too small to handle new character
				auto region = this->texture_atlas->get_region(character_width, character_height);
				this->texture_atlas->set_region(region, reinterpret_cast<byte*>(expanded_data), 4);
				delete expanded_data;
				const float inverted_texture_size = 1.0f / TEXTURE_SIZE;
				glyph.s0 = region.x * inverted_texture_size;
				glyph.s1 = (region.x + region.width) * inverted_texture_size;
				glyph.t0 = (region.y + region.height) * inverted_texture_size;
				glyph.t1 = region.y * inverted_texture_size;
			}
			glyph.width = character_width;
			glyph.height = character_height;
			glyph.offset_y = bitmap_glyph->top;
			glyph.offset_x = bitmap_glyph->left;
			glyph.rendermode = ds::fonts::Rendermode::RENDER_NORMAL;

			// TODO: get the correct values for the following entries
			glyph.kerning.push_back({ '0', 1 });
			glyph.kerning.push_back({ '0', 1 });
			glyph.outline_thickness = 2;

			FT_Load_Glyph(face, glyph_index, FT_LOAD_RENDER | FT_LOAD_NO_HINTING);
			glyph.advance_x = this->face->glyph->advance.x * SUBPIXEL_2_PIXEL;
			glyph.advance_y = this->face->glyph->advance.y * SUBPIXEL_2_PIXEL;
			this->glyph_cache.emplace(character, glyph);
			return std::move(glyph);
		}
	}
}