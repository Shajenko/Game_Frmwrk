#include "InputManager.h"
#include "GUIHelper.h"

#include <SDL_events.h>
#include <SDL_timer.h>

#include <CEGUI/Window.h>

InputManager::InputManager()
{
	//ctor
	init();
}

InputManager::InputManager(CEGUI::GUIContext * guiContext)
{
	_guiContext = guiContext;

	init();
}

void InputManager::init()
{
	_LastKeyState = NULL;
	_keyStateSize = new int;
	_CurrentKeyState = SDL_GetKeyboardState(_keyStateSize);
	_LastKeyState = new Uint8[*_keyStateSize];
	_mouseButtonState = SDL_GetMouseState(&_mouseX, &_mouseY);
	_lastMouseButtonState = _mouseButtonState;

	_keyStateChange = false;
	_mousePosChange = false;
	_mouseButtonChange = false;

	_mouseButtonDown = false;
	_mouseButtonUp = false;

	_lastKeyChanged = SDLK_SPACE;
	_lastMouseButtonChanged = SDL_BUTTON_LEFT;

	_lastTime = SDL_GetTicks();
}

InputManager::~InputManager()
{
	//dtor
	delete _LastKeyState;
}

int InputManager::CopyLastState()
{

    memcpy(_LastKeyState, _CurrentKeyState, *_keyStateSize * sizeof(Uint8));
    _lastMouseButtonState = _mouseButtonState;
    return 0;
}

bool InputManager::update(bool &keyboardFocus, bool &mouseFocus, bool &visible)
{
	using namespace CEGUI;
    bool quit = false;
    SDL_Event event;

	Key::Scan keyscan;
	MouseButton buttonscan;

	_keyStateChange = false;
	_mousePosChange = false;
	_mouseButtonChange = false;

	_mouseButtonDown = false;
	_mouseButtonUp = false;

	CopyLastState();

	if (_guiContext != nullptr)
	{
		// inject time pulse into CEGUI
		float currTime = SDL_GetTicks();
		_guiContext->injectTimePulse(currTime - _lastTime);
		_lastTime = currTime;
	}

    //Handle events on queue
    while(SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
			_keyStateChange = true;
			_lastKeyChanged = event.key.keysym.sym;
			if (_guiContext != nullptr)
			{				// inject the key into CEGUI
				keyscan = SDLKeyToCEGUIKey(event.key.keysym.sym);
				if (event.type == SDL_KEYDOWN)
					_guiContext->injectKeyDown(keyscan);
				if (event.type == SDL_KEYUP)
					_guiContext->injectKeyUp(keyscan);
			}
		}

        // Mouse movement
        if( event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP )
        {
            //Get mouse position
            int x, y;
            _mouseButtonState = SDL_GetMouseState( &x, &y );

            _mouseX = x;
            _mouseY = y;
			if (event.type == SDL_MOUSEMOTION)
			{
				_mousePosChange = true;
				if (_guiContext != nullptr)
				{
					// inject mouse data into CEGUI
					_guiContext->injectMousePosition(_mouseX * 1.0f, _mouseY * 1.0f);
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
			{
				_mouseButtonChange = true;
				_lastMouseButtonChanged = event.button.button;
				buttonscan = SDLButtonToCEGUIButton(_lastMouseButtonChanged);
				if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					_mouseButtonDown = true;
					// Get which mouse button was pressed
					if (_guiContext != nullptr)
					{
						// inject mouse button down into CEGUI
						_guiContext->injectMouseButtonDown(buttonscan);
					}

				}
				if (event.type == SDL_MOUSEBUTTONUP)
				{
					_mouseButtonUp = true;
					// Get which mouse button was pressed
					if (_guiContext != nullptr)
					{
						// inject mouse button up into CEGUI
						_guiContext->injectMouseButtonUp(buttonscan);
						
					}
				}
			}

        }
        if (event.type == SDL_WINDOWEVENT) {
            switch (event.window.event) {
            case SDL_WINDOWEVENT_SHOWN:
                visible = true;
                break;
            case SDL_WINDOWEVENT_HIDDEN:
                visible = false;
                break;
            case SDL_WINDOWEVENT_MINIMIZED:
                visible = false;
                break;
            case SDL_WINDOWEVENT_ENTER:
                mouseFocus = true;
                break;
            case SDL_WINDOWEVENT_LEAVE:
                mouseFocus = false;
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                keyboardFocus = true;
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                keyboardFocus = false;
                break;
            default:
                break;
            }
        }
        //User requests quit
        else if( event.type == SDL_QUIT )
        {
            printf("Quit state achieved\n");
            quit = true;
            return quit;
        }
    }


    return quit;
}

bool InputManager::keyDown(SDL_Keycode key)
{
	return (bool)_CurrentKeyState[SDL_GetScancodeFromKey(key)];
}

bool InputManager::keyPressed(SDL_Keycode key)
{
	if(_CurrentKeyState[SDL_GetScancodeFromKey(key)] && !_LastKeyState[SDL_GetScancodeFromKey(key)])
		return true;
	else
		return false;
}

void InputManager::mouseLocation(int &x, int &y)
{
    x = _mouseX;
    y = _mouseY;
}

bool InputManager::mouseDown(Uint8 mButton)
{
	return (_mouseButtonState & (bool)SDL_BUTTON(mButton));
}

bool InputManager::mousePressed(Uint8 mButton)
{
    return ((_mouseButtonState & (bool)SDL_BUTTON(mButton)) && !(_lastMouseButtonState & (bool)SDL_BUTTON(mButton)));
}

bool InputManager::mouseReleased(Uint8 mButton)
{
    return (!(_mouseButtonState & (bool)SDL_BUTTON(mButton)) && (_lastMouseButtonState & (bool)SDL_BUTTON(mButton)));
}
