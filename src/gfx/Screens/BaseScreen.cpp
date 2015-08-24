#include "BaseScreen.h"

#include <CEGUI/Window.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

BaseScreen::BaseScreen(unsigned int x, unsigned int y, unsigned int w, unsigned int h)
{
    //ctor
    _x = x;
    _y = y;
    _w = w;
    _h = h;

    _state = ACTIVE;
    _focused = false;
    _grabFocus = true;
    _name = "";

}

BaseScreen::~BaseScreen()
{

}

void BaseScreen::handleInput(InputManager * InputManager)
{

}

void BaseScreen::update()
{

}


void BaseScreen::draw(RenderEngine * rEngine)
{

}

void BaseScreen::unload()
{
	_state = SHUTDOWN;
}

SDL_Rect BaseScreen::getRect()
{
	SDL_Rect tempRect;

	tempRect.x = _x;
	tempRect.y = _y;
	tempRect.w = _w;
	tempRect.h = _h;

	return tempRect;
}

void BaseScreen::setRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h)
{
	_x = x;
	_y = y;
	_w = w;
	_h = h;
}

void BaseScreen::createGUIElements()
{

}

CEGUI::Window * BaseScreen::createButton(std::string buttonName, const glm::vec4 &destRectPerc, const glm::vec4 &destRectPix, std::string buttonText)
{
	CEGUI::Window *BtnWindow = nullptr;

	BtnWindow = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button", buttonName);  // Create Window
	BtnWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(destRectPerc.x, destRectPix.x), CEGUI::UDim(destRectPerc.y, destRectPix.y)));
	BtnWindow->setSize(CEGUI::USize(CEGUI::UDim(destRectPerc.z, destRectPix.z), CEGUI::UDim(destRectPerc.w, destRectPix.w)));
	BtnWindow->setText(buttonText);

	return BtnWindow;
}

CEGUI::Window * BaseScreen::createBaseWindow(std::string windowName, const glm::vec4 &destRectPerc, const glm::vec4 &destRectPix)
{
	CEGUI::Window * window;
	window = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage", windowName);
	window->setPosition(CEGUI::UVector2(CEGUI::UDim(destRectPerc.x, destRectPix.x), CEGUI::UDim(destRectPerc.y, destRectPix.y)));
	window->setSize(CEGUI::USize(CEGUI::UDim(destRectPerc.z, destRectPix.z), CEGUI::UDim(destRectPerc.w, destRectPix.w)));

	return window;
}