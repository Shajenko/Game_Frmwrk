#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>

#define FONT_LOC "C:/Windows/Fonts/"

#define WIDTH 400
#define HEIGHT 200

class Font
{
public:
    Font();
    ~Font();
    bool initLibrary();
    bool initFace(std::string filename, int width, int height);
    bool loadGlyph(char c);
    bool writeString(std::string text);
    void draw_bitmap( FT_Bitmap* bitmap, FT_Int x, FT_Int y);


    //int getGlyphWidth() { return _face->glyph->bitmap.width;}
    //int getGlyphHeight() { return _face->glyph->bitmap.rows;}
    int getBitmapWidth() {return _bitmapWidth;}
    int getBitmapHeight() {return _bitmapHeight;}




    unsigned char * getBitmap() { return _outputBitmap;}

protected:
private:
    FT_Library  _library;
    FT_Face     _face;      /* handle to face object */

    unsigned int _charWidth, _charHeight;

    unsigned char * _outputBitmap;
    unsigned int _bitmapWidth, _bitmapHeight;

};


#endif // FONT_H_INCLUDED
