#include "MenuEntry.h"

MenuEntry::MenuEntry(unsigned int x, unsigned int y, std::string text, bool enabled, bool selected)
{
    _x = x;
    _y = y;
    _rect.x = x;
    _rect.y = y;
    _text = text;
    _enabled = enabled;
    _selected = selected;
}

MenuEntry::MenuEntry(SDL_Rect rect, std::string text, bool enabled, bool selected)
{
    _x = rect.x;
    _y = rect.y;
    _rect.x = rect.x;
    _rect.y = rect.y;
    _text = text;
    _enabled = enabled;
    _selected = selected;

}

MenuEntry::~MenuEntry()
{

}

SDL_Rect MenuEntry::getRect()
{
    return _rect;
}

void MenuEntry::setRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h)
{
    _rect.x = x;
    _rect.y = y;
    _rect.w = w;
    _rect.h = h;
}

void MenuEntry::draw(SDL_Renderer * gRen)
{
    return;
}

bool MenuEntry::mouseOver(unsigned int mouseX, unsigned int mouseY)
{
    // Returns a boolean stating whether the mouse is over this button
    if((mouseX > _x ) && (mouseX <= _x + _w) && (mouseY > _y) && (mouseY < _y + _h))
        return true;
    else
        return false;
}

void MenuEntry::onMousePress()
{
    return;
}

void MenuEntry::onMouseDown()
{
    return;
}

void MenuEntry::onMouseRelease()
{
    return;
}

void MenuEntry::onMouseExit()
{
    return;
}

void MenuEntry::runCallback()
{
    return;
}
