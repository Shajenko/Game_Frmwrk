#include "font.h"
#include <string>
#include <iostream>
#include <math.h>

using namespace std;

#define HRES  64
#define HRESf 64.f
#define DPI   72




Font::Font()
{
    initLibrary();
    _outputBitmap = NULL;
    _bitmapWidth = 0;
    _bitmapHeight = 0;
}

Font::~Font()
{

}



bool Font::initLibrary()
{
    FT_Error error = FT_Init_FreeType( &_library );
    if ( error )
    {
        cerr << "Error initializing FreeType Library!" << endl;
        return false;
    }
    return true;
}


bool Font::initFace(std::string filename, int width, int height)  // width and height in font points
{
    _charWidth = width * HRES;
    _charHeight = height * HRES;

    FT_Error error = FT_New_Face( _library,
                     filename.c_str(),
                     0,
                     &_face );
    if ( error == FT_Err_Unknown_File_Format )
    {
        cerr << "Font format is unsupported!" << endl;
        return false;
    }
    else if ( error )
    {
        cerr << "File could not be opened properly!" << endl;
        return false;
    }

    /* Select charmap */
    /*error = FT_Select_Charmap(_face, FT_ENCODING_UNICODE);
    if(error) {
        cerr << "FT_Error Select Charmap!" << endl;
        FT_Done_Face(_face);
        FT_Done_FreeType(_library);
        return false;
    }*/

    error = FT_Set_Char_Size(
          _face,    /* handle to face object           */
          _charWidth,       /* char_width in 1/64th of points  */
          _charHeight,   /* char_height in 1/64th of points */
          DPI*HRES,     /* horizontal device resolution    */
          DPI );   /* vertical device resolution      */

    if (error)
    {
        cerr << "SetCharSize failed!" << endl;
        FT_Done_Face(_face);
        FT_Done_FreeType(_library);
        return false;
    }

    error = FT_Set_Pixel_Sizes(
          _face,   /* handle to face object */
          8,      /* pixel_width           */
          8 );   /* pixel_height          */

    if (error)
    {
        cerr << "SetPixelSizes failed!" << endl;
        return false;
    }

    FT_Matrix matrix = {
        (int)((1.0/HRES)      * 0x10000L),
        (int)((0.0)           * 0x10000L),
        (int)((0.0)           * 0x10000L),
        (int)((1.0)           * 0x10000L)};

    /* Set transform matrix */
    FT_Set_Transform(_face, &matrix, NULL);

    return true;
}

bool Font::loadGlyph(char c)
{
    FT_GlyphSlot  slot = _face->glyph;  /* a small shortcut */
    unsigned int glyph_index = FT_Get_Char_Index( _face, c );

    //_outputBitmap = NULL;

    if(glyph_index == 0)
    {
        cerr << "GetCharIndex failed!" << endl;
        return false;
    }

    FT_Error error = FT_Load_Glyph(
                    _face,          /* handle to face object */
                    glyph_index,   /* glyph index           */
                    FT_LOAD_DEFAULT );  /* load flags, see below */
    if(error)
    {
        cerr << "Failed to load glyph!" << endl;
        return false;
    }

    error = FT_Render_Glyph( slot,   /* glyph slot  */
                            FT_RENDER_MODE_NORMAL ); /* render mode */
    if(error)
    {
        cerr << "Failed to render glyph!" << endl;
        return false;
    }

/*    if( _outputBitmap == NULL)
        _outputBitmap = new unsigned char[_face->glyph->bitmap.width * _face->glyph->bitmap.rows];

    memset(_outputBitmap, 0xFFFFFFFF, _face->glyph->bitmap.width * _face->glyph->bitmap.rows);

    memcpy(_outputBitmap, _face->glyph->bitmap.buffer, _face->glyph->bitmap.width * _face->glyph->bitmap.rows);*/


    return true;
}

bool Font::writeString(std::string text)
{
    FT_Matrix     matrix;                 /* transformation matrix */
    FT_Vector     pen;                    /* untransformed origin  */
    FT_GlyphSlot  slot;
    FT_Error error;

    unsigned char letter;

    double        angle;
    int           target_height;
    int           n, num_chars;

    _bitmapWidth = 0;
    _bitmapHeight = 0;

    num_chars     = strlen( text.c_str() );
    angle         = ( 25.0 / 360 ) * 3.14159 * 2;      /* use 25 degrees     */
    target_height = HEIGHT;


    slot = _face->glyph;

    if( _outputBitmap == NULL)
        _outputBitmap = new unsigned char[WIDTH * HEIGHT + 1];

    memset(_outputBitmap, 0xFFFFFFFF, WIDTH * HEIGHT);

    /* set up matrix */
/*    matrix.xx = (FT_Fixed)( cos( angle ) * 0x10000L );
    matrix.xy = (FT_Fixed)(-sin( angle ) * 0x10000L );
    matrix.yx = (FT_Fixed)( sin( angle ) * 0x10000L );
    matrix.yy = (FT_Fixed)( cos( angle ) * 0x10000L );*/



    /* the pen position in 26.6 cartesian space coordinates; */
    /* start at (300,200) relative to the upper left corner  */
//    pen.x = 10 * 64;
//    pen.y = ( 10 ) * 64;
    pen.x = 15;
    pen.y = 5;

    for ( n = 0; n < num_chars; n++ )
    {
        /* set transformation */
        FT_Set_Transform( _face, NULL, &pen );
        letter = text[n];

        /* load glyph image into the slot (erase previous one) */
        error = FT_Load_Char( _face, text[n], FT_LOAD_RENDER );
        if ( error )
        {
            cerr << "Load Char failed!" << endl;
            continue;                 /* ignore errors */
        }


        /* now, draw to our target surface (convert position) */
        draw_bitmap( &slot->bitmap,
                     pen.x + slot->bitmap_left,
                     pen.y - slot->bitmap_top );

        _bitmapHeight += slot->bitmap.rows;
        _bitmapWidth += slot->bitmap.width;

        /* increment pen position */
        pen.x += slot->advance.x >> 6;
        //pen.y += slot->advance.y;
    }

    return true;
}

/* Replace this function with something useful. */


void
Font::draw_bitmap( FT_Bitmap*  bitmap,
             FT_Int      x,
             FT_Int      y)
{
//    unsigned char *image;

//    image = new unsigned char[WIDTH * HEIGHT];

    //memset( image, 0xFF00FF00, WIDTH * HEIGHT);

    FT_Int  i, j, p, q;
    FT_Int  x_max = x + bitmap->width;
    FT_Int  y_max = y + bitmap->rows;


    for ( i = x, p = 0; i < x_max; i++, p++ )
    {
        for ( j = y, q = 0; j < y_max; j++, q++ )
        {
          if ( i < 0      || j < 0       ||
               i >= WIDTH || j >= HEIGHT )
            continue;

          _outputBitmap[i + j * x_max] = bitmap->buffer[q * bitmap->width + p];
        }
    }
    //memcpy(_outputBitmap, image, WIDTH * HEIGHT);
}
