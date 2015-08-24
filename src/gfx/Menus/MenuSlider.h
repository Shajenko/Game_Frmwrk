#ifndef MENUSLIDER_H
#define MENUSLIDER_H

#include "MenuEntry.h"


class MenuSlider : public MenuEntry
{
    public:
        MenuSlider(unsigned int x, unsigned int y, std::string text, SDL_Renderer * ren, SDL_Surface * background, SDL_Surface * slideButton, SDL_Color color, std::function<void(int)> cllbk, TTF_Font * font, bool enabled = true, bool selected = false );
        MenuSlider(SDL_Rect rect, std::string text, SDL_Renderer * ren, SDL_Surface * background, SDL_Surface * slideButton, SDL_Color color, std::function<void(int)> cllbk, TTF_Font * font, bool enabled = true, bool selected = false);
        virtual ~MenuSlider();

        void setBackground(SDL_Surface * surf) {_background.loadFromSurface(surf);}
        void setSlideButton(SDL_Surface * surf) {_slideButton.loadFromSurface(surf);}
        void setLabel(std::string text, SDL_Color color) {_label.loadFromRenderedText(text, color);}
        void setFont(TTF_Font * font) {_font = font;}

        void setCallback(std::function<void(int)> cllbk) {_callback = cllbk;}
        void runCallback(int in) {_callback(in);}

        void setOffset(int offsetX, int offsetY) {_buttonOffsetX = offsetX; _buttonOffsetY = offsetY;}

        void setRange(int min, int max) {_min = min; _max = max;}
        void setValue(int value) {_value = value;}

        void onMousePress();
        void onMouseDown();
        void onMouseRelease();
        void onMouseExit();


        void draw(SDL_Renderer * gRen);

    protected:
    private:
        std::function<void(int)> _callback;
        std::string _labelStr;
        LTexture _background, _slideButton, _label;
        int _value;
        int _min, _max;
        int _buttonOffsetX, _buttonOffsetY;

        TTF_Font * _font;

};

#endif // MENUSLIDER_H
