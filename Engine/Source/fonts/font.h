#pragma once

#include <vector>
#include "core/types.h"

using namespace ds;

namespace ds {
	namespace fonts {
		enum Rendermode
		{
			RENDER_NORMAL,
			RENDER_OUTLINE_EDGE,
			RENDER_OUTLINE_POSITIVE,
			RENDER_OUTLINE_NEGATIVE,
			RENDER_SIGNED_DISTANCE_FIELD
		};


		/**
		 * A structure that hold a kerning value relatively to a Unicode
		 * codepoint.
		 *
		 * This structure cannot be used alone since the (necessary) right
		 * Unicode codepoint is implicitely held by the owner of this structure.
		 */
		struct Kerning
		{
			/**
			 * Left Unicode codepoint in the kern pair in UTF-32 LE encoding.
			 */
			uint32 codepoint;

			/**
			 * Kerning value (in fractional pixels).
			 */
			float kerning;

		};
		struct Glyph
		{
			/**
			 * Unicode codepoint this glyph represents in UTF-32 LE encoding.
			 */
			uint32 codepoint;

			/**
			 * Glyph's width in pixels.
			 */
			size_t width;

			/**
			 * Glyph's height in pixels.
			 */
			size_t height;

			/**
			 * Glyph's left bearing expressed in integer pixels.
			 */
			int offset_x;

			/**
			 * Glyphs's top bearing expressed in integer pixels.
			 *
			 * Remember that this is the distance from the baseline to the top-most
			 * glyph scanline, upwards y coordinates being positive.
			 */
			int offset_y;

			/**
			 * For horizontal text layouts, this is the horizontal distance (in
			 * fractional pixels) used to increment the pen position when the glyph is
			 * drawn as part of a string of text.
			 */
			float advance_x;

			/**
			 * For vertical text layouts, this is the vertical distance (in fractional
			 * pixels) used to increment the pen position when the glyph is drawn as
			 * part of a string of text.
			 */
			float advance_y;

			/**
			 * First normalized texture coordinate (x) of top-left corner
			 */
			float s0;

			/**
			 * Second normalized texture coordinate (y) of top-left corner
			 */
			float t0;

			/**
			 * First normalized texture coordinate (x) of bottom-right corner
			 */
			float s1;

			/**
			 * Second normalized texture coordinate (y) of bottom-right corner
			 */
			float t1;

			/**
			 * A vector of kerning pairs relative to this glyph.
			 */
			std::vector<Kerning> kerning;

			/**
			 * Mode this glyph was rendered
			 */
			Rendermode rendermode;

			/**
			 * Glyph outline thickness
			 */
			float outline_thickness;
		};
	}
}