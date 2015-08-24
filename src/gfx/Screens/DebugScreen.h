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
        SDL_Surface * draw();
        SDL_Texture * drawTex();
		void draw(RenderEngine * rEngine);
        void setChange();

        void SetScreens(std::string scrns) {_screens = scrns;}
        void SetFocusScreens(std::string fcscrns) {_focusScreen = fcscrns;}

    protected:
    private:
        std::string _screens;
        std::string _focusScreen;

        int _fps;
        int _fpsCounter;
        std::string _fpsText;
        double _fpsTimer;

        bool _updateTxt;

        Uint32 _lastTime;

		glm::vec4 _bgRect;

		glm::vec4 _textColor;
        float _alpha;

		Font * _font;
};

#endif // DEBUGSCREEN_H
