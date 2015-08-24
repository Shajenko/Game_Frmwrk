#include "TestScreen.h"

TestScreen::TestScreen(unsigned int x, unsigned int y, unsigned int w, unsigned int h) : BaseScreen(x, y, w, h)
{
	//ctor
	_textPosX = 20;
	_textPosY = 20;
	_startTime = clock();

//	state = ACTIVE;
	_focused = true;
	_grabFocus = true;

	_isAlive = true;
	_lifespan = 0.0;
	_name = "testScreen";


//	background = IMG_Load("gfx/roundRectBack640480.jpg");
//	returnScrn = IMG_Load("gfx/blackscreen.jpg");

	 //Open the font
	_font = new Font(12, "./res/arial.ttf");

	_backgrnd = new Texture("gfx/roundRectBack640480.jpg", GL_RGBA);
}

TestScreen::~TestScreen()
{
	delete _font;
	delete _backgrnd;
	//dtor
}

void TestScreen::update()
{
	if(_isAlive)
	{
		_curTime = clock();
		_lifespan = difftime(_curTime, _startTime) / (1.0 * CLOCKS_PER_SEC);
		if (_lifespan > 5.0)
			_isAlive = false;
	}

	if(!_isAlive)
		_state = SHUTDOWN;
}

void TestScreen::draw(RenderEngine * rEngine)
{
    std::ostringstream strs;
    

    strs << "Time to live: " << _lifespan << " seconds";
    _testText = strs.str();
	rEngine->drawSprite(_backgrnd, glm::vec4(_x*1.0f, _y*1.0f, _w*1.0f, _h*1.0f));
	rEngine->drawString(_testText.c_str(), glm::vec3(20.0f, 20.0f, 1.0f), _font);

    return;
}
