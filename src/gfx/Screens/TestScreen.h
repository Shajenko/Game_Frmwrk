#ifndef TESTSCREEN_H
#define TESTSCREEN_H

#include "BaseScreen.h"
#include "../Font.h"
#include "../OpenGL/texture.h"

class TestScreen : public BaseScreen
{
	public:
		TestScreen(unsigned int, unsigned int, unsigned int, unsigned int);
		virtual ~TestScreen();
        void update();
		void draw(RenderEngine * rEngine);
	protected:
	private:
		std::string _testText;
		unsigned int _textPosX, _textPosY;
		bool _isAlive;
		clock_t _startTime, _curTime, _aliveTime;
		double _lifespan;

		Texture * _backgrnd;


		//The font that's going to be used
		Font * _font;
		//The color of the font

};

#endif // TESTSCREEN_H
