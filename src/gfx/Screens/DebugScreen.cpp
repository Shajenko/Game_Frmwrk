#include "DebugScreen.h"

DebugScreen::DebugScreen(unsigned int x, unsigned int y, unsigned int w, unsigned int h) : BaseScreen(x, y, w, h)
{
    //ctor
    _name = "Debug Screen";
    _screens = "";
    _focusScreen = "";

    _fps = 0;
    _fpsCounter = 0;
    _fpsText = "FPS: 0";
    _fpsTimer = 0.0;

    _grabFocus = false;
    _state = HIDDEN;


    _lastTime = SDL_GetTicks();

//    _background = _globals->getTexture("Black Screen 600 450");

	_alpha = 0.5f;  // 0 = transparent, 1 = opaque

	_textColor = glm::vec4(1.0f, 1.0f, 1.0f, _alpha);

	_bgRect = glm::vec4(x * 1.0f + 20.0f, y * 1.0f + 20.0f, w * 1.0f - 20.0f, h * 1.0f - 20.0f);

	_font = new Font(20, "./res/arial.ttf");

    _updateTxt = true;
}

DebugScreen::~DebugScreen()
{
    //dtor
}


void DebugScreen::handleInput(InputManager * inputManager)
{
	if(inputManager->keyPressed(SDLK_F1))
	{
		if(_state == ACTIVE)
			_state = HIDDEN;
		else if (_state == HIDDEN)
			_state = ACTIVE;
	}
}

void DebugScreen::update()
{
/*    int txtWidth = 0, x;
    int txtHeight = 0, y;

//    TTF_SizeText(_font, _screens.c_str(), &x, &y);

    if(x > txtWidth)
        txtWidth = x;

//    TTF_SizeText(_font, _focusScreen.c_str(), &x, &y);

    if(x > txtWidth)
        txtWidth = x;

    TTF_SizeText(_font, _fpsText.c_str(), &x, &y);

    txtHeight = y * 3;*/

    _fpsTimer = (SDL_GetTicks() - _lastTime) / 1000.0f;

    if(_fpsTimer < 1.0)
    {
        _fpsCounter++;
    }
    else
    {
		if (_fps != _fpsCounter)
		{
			_updateTxt = true;
			_fpsText = "FPS: " + std::to_string(_fps);
		}
        _fps = _fpsCounter;
        _fpsCounter = 1;
        _lastTime = SDL_GetTicks();
        _fpsTimer = 0.0;
    }
}

void DebugScreen::draw(RenderEngine * rEngine)
{
	if (_state == ACTIVE)
	{
		rEngine->drawSprite(NULL, _bgRect, glm::vec4(0.5f, 0.5f, 0.5f, _alpha));
		rEngine->drawString(_fpsText, glm::vec3(_bgRect.x + 30.0f, _bgRect.y + 40.0f, 1.0f), _font, _textColor);
	}
}

void DebugScreen::setChange()
{
//    _updateTxt = true;
}
