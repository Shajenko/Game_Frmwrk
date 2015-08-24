#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <GL/glew.h> // needs to be before "SDL_opengl.h
#include <GL/gl.h>
#include <GL/glu.h>

#include "../Constants.h"
#include <stdio.h>
#include <cstring>

#include <SDL_keyboard.h>
#include <SDL_mouse.h>

#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>



class InputManager
{
public:
	InputManager();
	InputManager(CEGUI::GUIContext * guiContext);
	void init();

	virtual ~InputManager();
	const Uint8 * GetCurrentKeyState() { return _CurrentKeyState; }
	int CopyLastState();

	bool update(bool &keyboardFocus, bool &mouseFocus, bool &visible);
	bool keyDown(SDL_Keycode key);
	bool keyPressed(SDL_Keycode key);
	void mouseLocation(int &x, int &y);
	bool mouseDown(Uint8 mButton);
	bool mousePressed(Uint8 mButton);
	bool mouseReleased(Uint8 mButton);

	Uint32 getMouseButtonState() { return _mouseButtonState; }

	bool getKeyStateChange() { return _keyStateChange; }
	bool getMousePosChange() { return _mousePosChange; }
	bool getMouseButtonChange() { return _mouseButtonChange; }

	SDL_Keycode getLastKeyChanged() { return _lastKeyChanged; }

	float getMouseX() { return _mouseX * 1.0f; }
	float getMouseY() { return _mouseY * 1.0f; }

	bool getMouseButtonDown() { return _mouseButtonDown; }
	bool getMouseButtonUp() { return _mouseButtonUp; }
protected:
private:
	const Uint8 * _CurrentKeyState;
	Uint8 * _LastKeyState;
	int * _keyStateSize;
	int _mouseX, _mouseY;
	Uint32 _mouseButtonState;
	Uint32 _lastMouseButtonState;
	bool _keyStateChange;
	bool _mousePosChange;
	bool _mouseButtonChange, _mouseButtonUp, _mouseButtonDown;

	SDL_Keycode _lastKeyChanged;
	Uint8 _lastMouseButtonChanged;

	float _lastTime;

	CEGUI::GUIContext * _guiContext = nullptr;
};

#endif // INPUTMANAGER_H
