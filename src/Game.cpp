#include "Game.h"
#include "gfx\Screens\TitleScreen.h"
#include "gfx\Screens\TestScreen.h"

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

int Game::run()
{
	Uint32 delayTime = 0;
	Uint32 lastTime;

	std::cout << "Starting game\n";
	bool quit = false;

	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS ) == -1)
	{
		cout << "SDL Init fail" << endl;
		return false;
	}
	std::cout << "SDL Initialized\n";

	// TODO: Create window and do a loading screen

	lastTime = SDL_GetTicks();

   	_globals = new Globals();
	std::cout << "Globals created - ";

	delayTime = SDL_GetTicks() - lastTime;
	std::cout << delayTime << " ticks\n";
	lastTime = SDL_GetTicks();
	// Load Content

	// Add default screens
	_scrManager = new ScreenManager(_globals, (int)SCREEN_WIDTH, (int)SCREEN_HEIGHT);
	cout << "Screenmanager created - ";

	delayTime = SDL_GetTicks() - lastTime;
	std::cout << delayTime << " ticks\n";
	lastTime = SDL_GetTicks();

	_scrManager->addScreen(new TitleScreen(0, 0, (int)SCREEN_WIDTH, (int)SCREEN_HEIGHT));
	cout << "Title Screen added - ";

	//_scrManager->addScreen(new TestScreen(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	//cout << "Test Screen added - ";

	delayTime = SDL_GetTicks() - lastTime;
	std::cout << delayTime << " ticks\n";
	lastTime = SDL_GetTicks();

    while (quit == false)
    {
		/* Draw graphics on buffer */

		quit = _scrManager->update();

		_scrManager->draw();
    }

    delete _scrManager;

	//Quit SDL subsystems
	SDL_Quit();

    return 0;

}
