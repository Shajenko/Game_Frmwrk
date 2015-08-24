#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "MenuEntry.h"
#include <SDL.h>
#include <functional>
#include <string>

class MenuButton : public MenuEntry
{

    public:
        MenuButton(unsigned int x, unsigned int y, std::string text, SDL_Renderer * ren, SDL_Surface * surf, std::function<void()> cllbk, bool enabled = true, bool selected = false );
        MenuButton(SDL_Rect rect, std::string text, SDL_Renderer * ren, SDL_Surface * surf, std::function<void()> cllbk, bool enabled = true, bool selected = false);
        virtual ~MenuButton();

        void setTexture(SDL_Surface * surf) {_texture.loadFromSurface(surf);}
        void setTexture(std::string text, SDL_Color color) {_texture.loadFromRenderedText(text, color);}
        void setFont(TTF_Font * font) {_font = font;}

        void setCallback(std::function<void()> cllbk) {_callback = cllbk;}
        void runCallback() {_callback();}

        void onMouseDown();
        void onMousePress();
        void onMouseRelease();
        void onMouseExit();


        void draw(SDL_Renderer * gRen);

    protected:
    private:
        std::function<void()> _callback;
        LTexture _texture;
        TTF_Font * _font;
};

#endif // MENUBUTTON_H
