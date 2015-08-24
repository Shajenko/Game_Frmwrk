#ifndef BASESCREEN_H
#define BASESCREEN_H

#include "../../Globals.h"
#include "../../Constants.h"
#include "../../Input/InputManager.h"
#include "../RenderEngine.h"


// Do not directly use this class - only use it for inheritance

class BaseScreen
{
    public:
        BaseScreen(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
        virtual ~BaseScreen();

        unsigned int Getx() { return _x; }
        void Setx(unsigned int val) { _x = val; }
        unsigned int Gety() { return _y; }
        void Sety(unsigned int val) { _y = val; }
        unsigned int Getw() { return _w; }
        void Setw(unsigned int val) { _w = val; }
        unsigned int Geth() { return _h; }
        void Seth(unsigned int val) { _h = val; }
        void setGlobals(Globals * glbls) {_globals = glbls;}

		SDL_Rect getRect();
		void setRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h);

		virtual void createGUIElements();
		virtual CEGUI::Window * createButton(std::string buttonName, const glm::vec4 &destRectPerc, const glm::vec4 &destRectPix, std::string buttonText = "");
		virtual CEGUI::Window * createBaseWindow(std::string windowName, const glm::vec4 &destRectPerc, const glm::vec4 &destRectPix);

        std::string getName() {return _name;}
        void SetName(std::string nm) {_name = nm;}
        ScreenState getState() {return _state;}
        void setState(ScreenState stt) { _state = stt;}
        bool getFocus() {return _focused;}
        void setFocus(bool fcs) {_focused=fcs;}
		bool getGrabFocus() {return _grabFocus;}
        void setGrabFocus(bool fcs) {_grabFocus=fcs;}
		void setRenderEngine(RenderEngine * rEngine) { _rEngine = rEngine; }

        virtual void handleInput(InputManager *);
        virtual void update();
		virtual void draw(RenderEngine * rEngine);
        virtual void unload();
    protected:
		std::string _name;
    	ScreenState _state;
    	bool _focused;
    	bool _grabFocus;

        unsigned int _x;
        unsigned int _y;
        unsigned int _w;
        unsigned int _h;

		RenderEngine * _rEngine;

        Globals * _globals;
    private:

};

#endif // BASESCREEN_H
