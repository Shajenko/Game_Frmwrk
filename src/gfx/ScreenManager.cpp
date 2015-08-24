#include "ScreenManager.h"
#include "./OpenGL/shader.h"
#include <GL/glew.h> // needs to be before "SDL_opengl.h
#include <GL/glu.h>
#include "SDL_opengl.h"
#include "BatchRenderEngine.h"

#include "./OpenGL/freetype-gl/texture-font.h"




ScreenManager::ScreenManager(Globals * glbls, int width, int height)
{
	Uint32 lastTime, delayTime;

	_globals = glbls;

	_fullscreen = false;
	_sdl2 = true;

	lastTime = SDL_GetTicks();

	_renderEngine = new BatchRenderEngine(width, height);
	std::cout << "RenderEngine created - ";

	delayTime = SDL_GetTicks() - lastTime;
	std::cout << delayTime << " ticks\n";
	lastTime = SDL_GetTicks();

    _debugScrn = new DebugScreen(20, 20, width - 60, height - 60);
    addScreen(_debugScrn);
	std::cout << "DebugScreen created - ";

	delayTime = SDL_GetTicks() - lastTime;
	std::cout << delayTime << " ticks\n";
	lastTime = SDL_GetTicks();

    _inputManager = new InputManager(_renderEngine->getGUIContext());
	std::cout << "InputManager created - ";

	delayTime = SDL_GetTicks() - lastTime;
	std::cout << delayTime << " ticks\n";

    _frameStartTime = SDL_GetTicks();

	// Add textures

	_font = new Font(20, "./res/arial.ttf");
	std::cout << "Font created\n";

    _visible = false;
    _keyboardFocus = false;
    _mouseFocus = false;

    _counter = 0;

	_screens.clear();

}

ScreenManager::~ScreenManager()
{
	delete _renderEngine;
	delete _inputManager;


}



bool ScreenManager::update()
{
	list<BaseScreen *> keepList;
	list<BaseScreen *>::iterator it;
	list<BaseScreen *>::reverse_iterator rit;

	//BaseScreen * tmpScreen;

	bool quit = false;


	string scrns = "";

    scrns = "Screens: ";


	// Screen cleanup
	// Find all dead screens

    for(it=_screens.begin();it != _screens.end(); ++it)
    {
		if ((*it) != NULL){
			if ((*it)->getState() != SHUTDOWN && (*it)->getName() != "Debug Screen")
			{
				scrns += (*it)->getName() + ", ";
				keepList.push_back((*it));
				(*it)->setFocus(false);
			}
			else if ((*it)->getName() != "Debug Screen")
			{
				delete *it;
				_debugScrn->setChange();
			}
		}
		
    }

    _screens.clear();

	// Add new screens to manager list

	if(_newScreens.size() > 0)
        _debugScrn->setChange();
	for(it=_newScreens.begin();it != _newScreens.end(); ++it)
	{
		
		(*it)->setFocus(false);
		if((*it)->getName() != "Debug Screen")
        {
			keepList.push_back((*it));
			scrns += (*it)->getName() + ", ";
        }
	}

	_newScreens.clear();

	// Reset debug screen to top of list
    keepList.push_back(_debugScrn);
      scrns += _debugScrn->getName();


    _screens = keepList;
    keepList.clear();

	_debugScrn->SetScreens(scrns);

	// check for focus

	quit = _inputManager->update(_keyboardFocus, _mouseFocus, _visible);
    if(quit)
        return quit;

    if(_visible || _mouseFocus || _keyboardFocus)
        _debugScrn->setChange();

	// Check screen focus
	if (_screens.size() > 0)
	{
//	    _debugScrn->SetFocusScreens("Focused: None");
		for(rit=_screens.rbegin();rit != _screens.rend(); ++rit)
		{
			if (*rit != NULL)
			{
				if ((*rit)->getState() == ACTIVE && (*rit)->getGrabFocus() == true)
				{
					(*rit)->setFocus(true);
					_debugScrn->SetFocusScreens("Focused: " + (*rit)->getName());
					break;
				}
			}
			
		}
		for(it=_screens.begin();it != _screens.end(); ++it)
		{
			if ((*it) != NULL)
			{
				if (_mouseFocus || _keyboardFocus)  // App has focus
				{
					(*it)->handleInput(_inputManager);
				}
				(*it)->update();
			}
		}
	}

	_counter += 0.01f;

	return false;
}

void ScreenManager::draw()
{
	//	list<BaseScreen *>::iterator it;

	list<BaseScreen *>::iterator it;

	Uint32 elapsedTime;
	Uint32 waitTime = (Uint32)(1000.0f / MAX_FRAMES);
	Sint32 delayTime = 0;

	for (it = _screens.begin(); it != _screens.end(); ++it)
	{
		if ((*it) != NULL)
			(*it)->draw(_renderEngine);
	}

	//Update screen

	_renderEngine->render();

	// Delay to maintain frame rate
	elapsedTime = (SDL_GetTicks() - _frameStartTime);
	delayTime = waitTime - elapsedTime;

	if (delayTime > 0)
	{
		elapsedTime += delayTime;
		SDL_Delay(delayTime);
		//std::cout << "Delaytime : " << delayTime << std::endl;
	}
	_frameStartTime = SDL_GetTicks();

}


void ScreenManager::addScreen(BaseScreen * scrn)
{
	_debugScrn->setChange();
	_newScreens.push_back(scrn);
	scrn->setRenderEngine(_renderEngine);
	scrn->createGUIElements();
}

void ScreenManager::unloadScreen(string scrnName)
{
	list<BaseScreen *>::iterator it;
	BaseScreen * tmpScreen;

	for(it=_screens.begin();it != _screens.end(); ++it)
	{
		tmpScreen = *it;
		if(tmpScreen->getName() == scrnName)
		{
			tmpScreen->unload();
			break;
		}
	}
}
