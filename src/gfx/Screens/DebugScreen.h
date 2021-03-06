#ifndef DEBUGSCREEN_H
#define DEBUGSCREEN_H

#include "BaseScreen.h"
#include "../Font.h"


class DebugScreen : public BaseScreen
{
    public:
        DebugScreen(unsigned int, unsigned int, unsigned int, unsigned int);
        virtual ~DebugScreen();

        void handleInput(InputManager *);
        void update();
		void draw(RenderEngine * rEngine);
        void setChange();
		void updateFPS(GLuint dfps, GLuint ufps); 

        void SetScreens(std::string scrns) {_screens = scrns;}
        void SetFocusScreens(std::string fcscrns) {_focusScreen = fcscrns;}

    protected:
    private:
        std::string _screens;
        std::string _focusScreen;

        unsigned int _dfps, _ufps, _ticks;
        std::string _dfpsText, _ufpsText, _testText;
		char _letter;

		glm::vec4 _bgRect;

		glm::vec4 _textColor;
        float _alpha;

		Font * _font;

		Texture * _tex;
};

#endif // DEBUGSCREEN_H
