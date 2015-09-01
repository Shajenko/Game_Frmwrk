#include "ScreenManager.h"
#include "./OpenGL/shader.h"
#include <GL/glew.h> // needs to be before "SDL_opengl.h
#include <GL/glu.h>
#include "SDL_opengl.h"
#include "BatchRenderEngine.h"

#include "./OpenGL/freetype-gl/texture-font.h"

const Uint32 upWaitTime = (Uint32)(1000.0f / MAX_UPDATE_FRAMES);
const Uint32 drWaitTime = (Uint32)(1000.0f / MAX_DRAW_FRAMES);

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

    _drawFrameStartTime = _drawSec = SDL_GetTicks();
	_updateFrameStartTime = _updateSec = SDL_GetTicks();
	_currTime = SDL_GetTicks();

	// Add textures

	_font = new Font(20, "./res/arial.ttf");
	std::cout << "Font created\n";

    _visible = false;
    _keyboardFocus = false;
    _mouseFocus = false;

	_screens.clear();

}

ScreenManager::~ScreenManager()
{
	delete _renderEngine;
	delete _inputManager;
}



bool ScreenManager::update()
{
	Uint32 elapsedTime;
	Sint32 delayTime = 0;

	// Delay to maintain frame rate
	_currTime = SDL_GetTicks();
	elapsedTime = (_currTime - _updateFrameStartTime);
	delayTime = upWaitTime - elapsedTime;
	if (delayTime > 0)
		return false;
	_uframeCount++;
	

	//BaseScreen * tmpScreen;

	bool quit = false;


	string scrns = "";

    scrns = "Screens: ";


	// Screen cleanup
	// Find all dead screens

    for(_it=_screens.begin();_it != _screens.end(); ++_it)
    {
		if ((*_it) != NULL){
			if ((*_it)->getState() != SHUTDOWN && (*_it)->getName() != "Debug Screen")
			{
				scrns += (*_it)->getName() + ", ";
				_keepList.push_back((*_it));
				(*_it)->setFocus(false);
			}
			else if ((*_it)->getName() != "Debug Screen")
			{
				delete *_it;
				_debugScrn->setChange();
			}
		}
		
    }

    _screens.clear();

	// Add new screens to manager list

	if(_newScreens.size() > 0)
        _debugScrn->setChange();
	for(_it=_newScreens.begin();_it != _newScreens.end(); ++_it)
	{
		
		(*_it)->setFocus(false);
		if((*_it)->getName() != "Debug Screen")
        {
			_keepList.push_back((*_it));
			scrns += (*_it)->getName() + ", ";
        }
	}

	_newScreens.clear();

	// Reset debug screen to top of list
    _keepList.push_back(_debugScrn);
      scrns += _debugScrn->getName();


    _screens = _keepList;
    _keepList.clear();

	_debugScrn->SetScreens(scrns);

	// check for focus

	quit = _inputManager->update(_keyboardFocus, _mouseFocus, _visible);
    if(quit)
        return quit;

    if(_visible || _mouseFocus || _keyboardFocus)
        _debugScrn->setChange();

	if (_currTime - _updateSec >= 1000) // end of second, update fps
	{
			_debugScrn->updateFPS(_dframeCount, _uframeCount);
			std::cout << "FPS Update: Draw FPS: " << _dframeCount << " Update FPS: " << _uframeCount << std::endl;
			_dframeCount = 0;
			_uframeCount = 0;
			_updateSec = _currTime;
			_drawSec = _currTime;
	}

	// Check screen focus
	if (_screens.size() > 0)
	{
		_debugScrn->SetFocusScreens("Focused: None");
		for(_rit=_screens.rbegin();_rit != _screens.rend(); ++_rit)
		{
			if (*_rit != NULL)
			{
				if ((*_rit)->getState() == ACTIVE && (*_rit)->getGrabFocus() == true)
				{
					(*_rit)->setFocus(true);
					_debugScrn->SetFocusScreens("Focused: " + (*_rit)->getName());
					break;
				}
			}
			
		}
		for(_it=_screens.begin();_it != _screens.end(); ++_it)
		{
			if ((*_it) != NULL)
			{
				if (_mouseFocus || _keyboardFocus)  // App has focus
				{
					(*_it)->handleInput(_inputManager);
				}
				(*_it)->update();
			}
		}
	}

	_updateFrameStartTime = SDL_GetTicks();

	return false;
}

void ScreenManager::draw()
{
	Uint32 elapsedTime;
	Sint32 delayTime = 0;

	// Delay to maintain frame rate
	_currTime = SDL_GetTicks();
	elapsedTime = (_currTime - _drawFrameStartTime);
	delayTime = drWaitTime - elapsedTime;
	if (delayTime > 0)
	{
		//SDL_Delay(1);
		return;
	}

	_dframeCount++;

	for (_it = _screens.begin(); _it != _screens.end(); ++_it)
	{
		if ((*_it) != NULL)
			(*_it)->draw(_renderEngine);
	}

	//Update screen

	_renderEngine->render();

	_drawFrameStartTime = SDL_GetTicks();
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
