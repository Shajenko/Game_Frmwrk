#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "../Constants.h"
#include "../Globals.h"

#include "./Screens/BaseScreen.h"
#include "./Screens/DebugScreen.h"
#include "../Initialization.h"

#include "../Input/InputManager.h"

//#include "./OpenGL/shader.h"
//#include "./OpenGL/mesh.h"
//#include "./OpenGL/texture.h"
//#include "./OpenGL/Transform.h"
//#include "./OpenGL/font.h"

#include "RenderEngine.h"

#include "./OpenGL/freetype-gl/texture-font.h"
#include "./OpenGL/freetype-gl/texture-atlas.h"
#include "./OpenGL/freetype-gl/vertex-buffer.h"

#include "Font.h"

#include <list>




using namespace std;

class ScreenManager
{
	public:
		ScreenManager(Globals * glbls, int width, int height);
		virtual ~ScreenManager();
//		bool dvlInit();
		bool update();
		void draw();
		void addScreen(BaseScreen *);
		void unloadScreen(string);
		void setGlobals(Globals * glbls) {_globals = glbls;}

		//void drawString(const std::string& text, const glm::vec3& position, const glm::vec4& color);

	protected:
	private:
		list<BaseScreen *> _screens;
		list<BaseScreen *> _newScreens;

		RenderEngine * _renderEngine = nullptr;

        DebugScreen *_debugScrn = nullptr;
        InputManager * _inputManager = nullptr;

		bool _fullscreen, _mouseFocus, _keyboardFocus, _visible, _sdl2;

		Uint32 _frameStartTime;

        Globals * _globals;

        float _counter;
		int _strLength;

		Font * _font;
};

#endif // SCREENMANAGER_H
