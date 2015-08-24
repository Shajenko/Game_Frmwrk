#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "BaseScreen.h"
#include <cstdlib>
#include <functional>
#include <CEGUI/Window.h>


enum MenuState {MAIN_MENU, OPTIONS_MENU, VOLUME_MENU, CREDITS_MENU};

class TitleScreen : public BaseScreen
{
	public:
		TitleScreen(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
		virtual ~TitleScreen();

		void handleInput(InputManager * inputM);
		void update();
		void draw(RenderEngine * rEngine);
		void unload();

		void createGUIElements();

		// Menu functions
		bool buttonPress(const CEGUI::EventArgs& e);

	protected:
		void activateMenu(CEGUI::Window * menu);

	private:
		double _aniTime;
		float _r, _g, _b;

		MenuState _mState;

		unsigned int _ticks;
		std::string _output1, _output2;

		Font *_smallFont, *_largeFont;

		int _volume;

		// CEGUI Stuff
		// Menus
		CEGUI::Window * _mainMenu, *_optionsMenu, *_volumeMenu; // *_volumeMenu;

		CEGUI::Slider *_musicVol, *_soundEffVol;

		Texture * _backgrndTex, * _testTex;
};

#endif // TITLESCREEN_H
