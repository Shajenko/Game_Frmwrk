#ifndef FONT_H
#define FONT_H

#include "../Constants.h"
#include "../Globals.h"

#include "../Initialization.h"

#include "./OpenGL/freetype-gl/texture-font.h"
#include "./OpenGL/freetype-gl/texture-atlas.h"
#include "./OpenGL/freetype-gl/vertex-buffer.h"



class Font
{
public:
	Font(unsigned int size, std::string path);
	ftgl::texture_font_t* getFont() { return _font; }
	ftgl::texture_atlas_t * getAtlas() { return _atlas; }
private:
	ftgl::texture_font_t * _font;
	ftgl::texture_atlas_t * _atlas;
};

#endif // FONT_H