#include "MenuButton.h"

MenuButton::MenuButton(unsigned int x, unsigned int y, std::string text, SDL_Renderer * ren, SDL_Surface * surf, std::function<void()> cllbk, bool enabled, bool selected ) : MenuEntry(x, y, text, enabled, selected)
{
    //ctor
    _texture.setRenderer(ren);
    _texture.loadFromSurface(surf);
    _w = _texture.getWidth();
    _h = _texture.getHeight();
    setCallback(cllbk);
    if(getEnabled())
        _texture.setColor(255, 255, 255);
    else
        _texture.setColor(100, 100, 100);
}

MenuButton::MenuButton(SDL_Rect rect, std::string text, SDL_Renderer * ren, SDL_Surface * surf, std::function<void()> cllbk, bool enabled, bool selected) : MenuEntry(rect, text, enabled, selected)
{
    _texture.setRenderer(ren);
    _texture.loadFromSurface(surf);
    _w = _texture.getWidth();
    _h = _texture.getHeight();
    setCallback(cllbk);
    if(getEnabled())
        _texture.setColor(255, 255, 255);
    else
        _texture.setColor(100, 100, 100);
}

MenuButton::~MenuButton()
{
    //dtor
}

void MenuButton::onMouseDown()
{
    // Change the color modulation on the button when the mouse is held down over it
    if(getEnabled())
        _texture.setColor(200, 200, 200);
    else
        _texture.setColor(100, 100, 100);

}

void MenuButton::onMousePress()
{
    // Change the color modulation on the button when the mouse is held down over it
    if(getEnabled())
        _texture.setColor(200, 200, 200);
    else
        _texture.setColor(100, 100, 100);
}

void MenuButton::onMouseRelease()
{
    // When the mouse button is released, call the function originally passed to this menu button
    _callback();
    if(getEnabled())
        _texture.setColor(255, 255, 255);
    else
        _texture.setColor(100, 100, 100);

}

void MenuButton::onMouseExit()
{
    if(getEnabled())
        _texture.setColor(255, 255, 255);
    else
        _texture.setColor(100, 100, 100);
}

void MenuButton::draw(SDL_Renderer * gRen)
{
    _texture.render(_x, _y);
}
