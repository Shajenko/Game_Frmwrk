#ifndef MAINMENU_H
#define MAINMENU_H

#include "MenuScreen.h"
#include "MenuEntry.h"

enum MenuTypes
{
	NEW_GAME,
	CONTINUE_GAME,
	OPTIONS,
	CREDITS
};

class MainMenu : public MenuScreen
{
	public:
		MainMenu(unsigned int, unsigned int, unsigned int, unsigned int, Globals * globals, ScreenManager * scrnmgr);
		virtual ~MainMenu();
		void addEntries(string text, bool enabled);

		void handleInput(InputManager *);
        void update();
        SDL_Surface * draw();
        void draw(SDL_Renderer *);
        void unload();
        void createTextures(SDL_Renderer * gRen);
	protected:
	private:
		list<MenuEntry *> entries;
		int menuSelect;

		SDL_Rect menuRect;
		SDL_Surface * tempSurf;
		SDL_Texture * bkgrndTexture;
};

#endif // MAINMENU_H
