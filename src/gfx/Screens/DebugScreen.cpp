#include "DebugScreen.h"

DebugScreen::DebugScreen(unsigned int x, unsigned int y, unsigned int w, unsigned int h) : BaseScreen(x, y, w, h)
{
    //ctor
    _name = "Debug Screen";
    _screens = "";
    _focusScreen = "";

    _dfps = 0;
	_ufps = 0;
	_ticks = 0;
    _dfpsText = "Draw FPS: 0";
	_ufpsText = "Update FPS: 0";
	_testText = "ABC";
	_letter = 'A';


    _grabFocus = false;
    _state = HIDDEN;

	_alpha = 0.5f;  // 0 = transparent, 1 = opaque

	_textColor = glm::vec4(1.0f, 1.0f, 1.0f, _alpha);

	_bgRect = glm::vec4(x * 1.0f + 20.0f, y * 1.0f + 20.0f, w * 1.0f - 20.0f, h * 1.0f - 20.0f);

	_font = new Font(18, "./res/arial.ttf");

	_tex = new Texture(_font->getAtlas()->id);
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
	_tex->loadFromID(_font->getAtlas()->id);

	// Increment animation time
	_ticks++;

	if (_ticks % 30 == 0)
	{
		_letter++;
		if (_letter > 'z')
			_letter = 'A';
		_ticks = 0;
		if (_testText.size() > 10)
			_testText = "jjj";
		_testText += _letter;
	}
}

void DebugScreen::draw(RenderEngine * rEngine)
{
	if (_state == ACTIVE)
	{
		rEngine->drawSprite(NULL, _bgRect, glm::vec4(0.5f, 0.5f, 0.5f, _alpha));
		rEngine->drawSprite(_tex, glm::vec4(40.0f, 400.0f, 550.0f, 500.0f));
		rEngine->drawString(_dfpsText, glm::vec3(_bgRect.x + 30.0f, _bgRect.y + 40.0f, 1.0f), _font, _textColor);
		rEngine->drawString(_ufpsText, glm::vec3(_bgRect.x + 30.0f, _bgRect.y + 80.0f, 1.0f), _font, _textColor);
		rEngine->drawString(_testText, glm::vec3(_bgRect.x + 30.0f, _bgRect.y + 120.0f, 1.0f), _font, _textColor);
	}
}

void DebugScreen::setChange()
{
//    _updateTxt = true;
}

void DebugScreen::updateFPS(GLuint dfps, GLuint ufps)
{ 
	_dfps = dfps; 
	_ufps = ufps; 
	_dfpsText = "Draw FPS: " + std::to_string(_dfps);
	_ufpsText = "Update FPS: " + std::to_string(_ufps);
	//std::cout << _dfpsText << std::endl << _ufpsText << std::endl;

}