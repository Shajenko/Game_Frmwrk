#ifndef MENUENTRY_H
#define MENUENTRY_H

#include "../../Constants.h"
#include <functional>

class MenuEntry
{
    protected:
        string _text;
        bool _enabled;
        bool _selected;
        SDL_Rect _rect;
        unsigned int _x, _y, _w, _h;

    public:
        LTexture _texture;

        MenuEntry(unsigned int x, unsigned int y, std::string text, bool enabled=true, bool selected=true);
        MenuEntry(SDL_Rect rect, std::string text, bool enabled = true, bool selected = true);
        virtual ~MenuEntry();

        unsigned int Getx() { return _x; }
        void Setx(unsigned int val) { _x = val; }
        unsigned int Gety() { return _y; }
        void Sety(unsigned int val) { _y = val; }
        unsigned int Getw() { return _w; }
        void Setw(unsigned int val) { _w = val; }
        unsigned int Geth() { return _h; }
        void Seth(unsigned int val) { _h = val; }

        void setSelected(bool selected) {_selected = selected;}

		SDL_Rect getRect();
		void setRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h);

        std::string getText() {return _text;}
        void setText(std::string nm) {_text = nm;}

        bool getEnabled() {return _enabled;}
        void setEnabled(bool en) {_enabled = en;}

        virtual void draw(SDL_Renderer * gRen);

        virtual bool mouseOver(unsigned int mouseX, unsigned int mouseY);

        virtual void onMousePress();
        virtual void onMouseDown();
        virtual void onMouseRelease();
        virtual void onMouseExit();

        virtual void runCallback();
};


#endif // MENUENTRY_H
