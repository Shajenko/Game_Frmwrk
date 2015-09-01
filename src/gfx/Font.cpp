#include "Font.h"

Font::Font(unsigned int size, std::string path)
{
	_atlas = ftgl::texture_atlas_new(60 * size, 80 * size, 2); // altas needs to be big enough to encompass all the characters at the font size
	_font = ftgl::texture_font_new_from_file(_atlas, (float)size, path.c_str());

	// Build a new vertex buffer (position, texture & color)
	//_FTBuffer = ftgl::vertex_buffer_new("vertex:3f,tex_coord:2f,color:4f");

	ftgl::texture_font_load_glyphs(_font, L" ABCDEFGHIJKLMNO");
	ftgl::texture_font_load_glyphs(_font, L" PQRSTUVWXYZ");
	ftgl::texture_font_load_glyphs(_font, L" abcdefghijklmno");
	ftgl::texture_font_load_glyphs(_font, L" pqrstuvwxyz{|}~");
	ftgl::texture_font_load_glyphs(_font, L" .!?,@[\\]^_`");
}
