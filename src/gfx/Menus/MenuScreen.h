#ifndef MENUSCREEN_H
#define MENUSCREEN_H

//#include "../BaseScreen.h"
#include "../ScreenManager.h"
#include "MenuEntry.h"
#include "MenuButton.h"
#include "MenuSlider.h"
#include <list>
#include <Windows.h>


class MenuScreen : public BaseScreen
{
    public:
        MenuScreen(int x, int y, int w, int h, Globals * globals);
        ~MenuScreen();

        //void createTextures(SDL_Renderer * gRen);
		void handleInput(InputManager * input);
		void update();
//		virtual SDL_Surface * draw();
		void draw(SDL_Renderer *);
		void unload();
		void addMenuEntry(MenuEntry * entry);
		//void addMenuEntry(bool enable, std::string menuName, TTF_Font * fnt, SDL_Rect rect, SDL_Renderer * ren);
		void setBackground(std::string bkgndFile);
//		MenuEntry * getChosen();

		void setScreenManager(ScreenManager * scrnmgr) {_screenMngr = scrnmgr;}
    protected:
        ScreenManager * _screenMngr;
    private:
        list<MenuEntry *> _entryList;
        MenuEntry  *_selectedEntry, *_lastClickedEntry;
		int _menuSelect;
		int _nextMenuY;

		SDL_Rect _menuRect;
		LTexture _bkgrndTexture;
};

#endif // MENUSCREEN_H
