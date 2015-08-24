#include "MenuSlider.h"

MenuSlider::MenuSlider(unsigned int x, unsigned int y, std::string text, SDL_Renderer * ren, SDL_Surface * background, SDL_Surface * slideButton, SDL_Color color, std::function<void(int)> cllbk, TTF_Font * font,  bool enabled, bool selected ) : MenuEntry(x, y, text, enabled, selected)
{
    //ctor

    setFont(font);
    _background.setRenderer(ren);
    _slideButton.setRenderer(ren);
    _label.setRenderer(ren);

    _background.loadFromSurface(background);
    _slideButton.loadFromSurface(slideButton);
    _label.setFont(font);
    _label.loadFromRenderedText(text, color);
    _labelStr = text;

    _w = _background.getWidth();
    _h = _background.getHeight();


    setCallback(cllbk);


}

MenuSlider::MenuSlider(SDL_Rect rect, std::string text, SDL_Renderer * ren, SDL_Surface * background, SDL_Surface * slideButton, SDL_Color color, std::function<void(int)> cllbk, TTF_Font * font, bool enabled, bool selected) : MenuEntry(rect, text, enabled, selected)
{
    setFont(font);
    _background.setRenderer(ren);
    _slideButton.setRenderer(ren);
    _label.setRenderer(ren);

    _background.loadFromSurface(background);
    _slideButton.loadFromSurface(slideButton);
    _label.setFont(font);
    _label.loadFromRenderedText(text, color);
    _labelStr = text;

    _w = _background.getWidth();
    _h = _background.getHeight();

    setCallback(cllbk);
}

MenuSlider::~MenuSlider()
{
    //dtor
    _background.free();
    _slideButton.free();
    _label.free();
}

void MenuSlider::onMousePress()
{
    // If the mouse is over the slider button

    // If the mouse is to the left of the slider button

    // If the mouse is to the right of the slider button
}

void MenuSlider::onMouseDown()
{
    // If the mouse is over the slider button

    // If the mouse is to the left of the slider button

    // If the mouse is to the right of the slider button
}

void MenuSlider::onMouseRelease()
{

}

void MenuSlider::onMouseExit()
{

}

void MenuSlider::draw(SDL_Renderer * gRen)
{
    _background.render(_x, _y);
    _slideButton.render(_x + _value + _buttonOffsetX, _y + _buttonOffsetY);
    _label.render(_x + (_w/2) - (_label.getWidth() / 2), _y);
}
