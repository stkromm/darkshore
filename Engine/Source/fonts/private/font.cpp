#include "fonts/font.h"

#include "third_party/freetype/ftglyph.h"
#include "platform/resource_handle.h"

namespace ds {
	namespace fonts {

		Font::Font(std::string path) {
			// Create And Initilize A FreeType Font Library.
			if (FT_Init_FreeType(&library))
				throw std::runtime_error("FT_Init_FreeType failed");

			// The Object In Which FreeType Holds Information On A Given
			// Font Is Called A "face".
			// This Is Where We Load In The Font Information From The File.
			// FT_New_Face Will Fail If The Font File Does Not Exist Or Is Somehow Broken.
			if (FT_New_Face(library, get_res_folder_path(FONT, path).c_str(), 0, &this->face))
				throw std::runtime_error("FT_New_Face failed (there is probably a problem with your font file)");

			/* We Don't Need The Face Information Now That The Display
			// Lists Have Been Created, So We Free The Assosiated Resources.
			FT_Done_Face(face);

			// Ditto For The Font Library.
			FT_Done_FreeType(library);
			*/
			this->texture_atlas = std::make_shared<ds::graphics::TextureAtlas>(512, 512, 4);
		}
		std::shared_ptr<graphics::Texture> Font::get_texture() {
			return this->texture_atlas->get_texture();
		}
		Glyph Font::get_glyph(char character) {
			auto cached_glyph = this->glyph_cache.find(character);
			if (cached_glyph != this->glyph_cache.end()) {
				return cached_glyph->second;
			}
			// For Some Twisted Reason, FreeType Measures Font Size
			// In Terms Of 1/64ths Of Pixels.  Thus, To Make A Font
			// h Pixels High, We Need To Request A Size Of h*64.
			// (h << 6 Is Just A Prettier Way Of Writing h*64)
			FT_Set_Char_Size(face, 0, 72 << 6, 72, 72);

			// Load The Glyph For Our Character.
			auto glyph_index = FT_Get_Char_Index(this->face, character);
			if (FT_Load_Glyph(this->face, glyph_index, FT_LOAD_DEFAULT))
				throw std::runtime_error("FT_Load_Glyph failed");

			Glyph glyph;
			glyph.codepoint = character;
			// Move The Face's Glyph Into A Glyph Object.
			FT_Glyph ft_glyph;
			glyph.width = this->face->glyph->metrics.width * (1 / 26.6f);
			glyph.height = this->face->glyph->metrics.height * (1 / 26.6f);
			glyph.advance_x = this->face->glyph->metrics.vertAdvance * (1 / 26.6f);
			glyph.advance_y = this->face->glyph->metrics.horiAdvance * (1/ 26.6f);
			glyph.offset_y = this->face->glyph->metrics.vertBearingY * (-1 / 26.6f);
		
			auto glyph_error = FT_Get_Glyph(this->face->glyph, &ft_glyph);
			if (glyph_error)
				throw std::runtime_error("FT_Get_Glyph failed" + glyph_error);

			// Convert The Glyph To A Bitmap.
			FT_Glyph_To_Bitmap(&ft_glyph, ft_render_mode_normal, 0, 1);
			FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)ft_glyph;

			// This Reference Will Make Accessing The Bitmap Easier.
			FT_Bitmap& bitmap = bitmap_glyph->bitmap;
			// Use Our Helper Function To Get The Widths Of
			// The Bitmap Data That We Will Need In Order To Create
			// Our Texture.
			int character_width = bitmap.width; // next_p2(bitmap.width);
			int character_height = bitmap.rows; // next_p2(bitmap.width);

			// Allocate Memory For The Texture Data.
			int* expanded_data = new int[character_width * character_height];

			// Here We Fill In The Data For The Expanded Bitmap.
			// Notice That We Are Using A Two Channel Bitmap (One For
			// Channel Luminosity And One For Alpha), But We Assign
			// Both Luminosity And Alpha To The Value That We
			// Find In The FreeType Bitmap.
			// We Use The ?: Operator To Say That Value Which We Use
			// Will Be 0 If We Are In The Padding Zone, And Whatever
			// Is The FreeType Bitmap Otherwise.
			for (int j = 0; j < character_height; j++) {
				for (int i = 0; i < character_width; i++) {
					auto bitmapValue = (i >= bitmap.width || j >= bitmap.rows) ? 0 : (bitmap.buffer[i + bitmap.width*j]);
					expanded_data[(i + j * character_width)] = (bitmapValue << 8) | (bitmapValue << 16) | (bitmapValue << 24) | 0xFF;
				}
			}

			auto region = this->texture_atlas->get_region(character_width, character_height);
			this->texture_atlas->set_region(region, reinterpret_cast<byte*>(expanded_data), 4);
			glyph.s0 = region.x * (1.0f / 512);
			glyph.s1 = (region.x + region.width) * (1.0f / 512);
			glyph.t0 = (region.y + region.height) * (1.0f / 512);
			glyph.t1 = region.y * (1.0f / 512);
			glyph.offset_x = 2;
			glyph.rendermode = ds::fonts::Rendermode::RENDER_NORMAL;
			glyph.kerning.push_back({ '0', 1 });
			glyph.kerning.push_back({ '0', 1 });
			glyph.outline_thickness = 2;

			this->glyph_cache.emplace(character, glyph);

			return glyph;
		}
	}
}