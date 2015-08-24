#include "MenuScreen.h"

MenuScreen::MenuScreen(int x, int y, int w, int h, Globals * globals) : BaseScreen(x, y, w, h)
{

	cout << "MenuScreen constructor\n";

    //ctor
    setGlobals(globals);

	//ctor
	_menuRect.x = x;
	_menuRect.y = y;
	_menuRect.w = w;
	_menuRect.h = h;

	_menuSelect = 0;
	_selectedEntry = NULL;
	_lastClickedEntry = NULL;

//	name = "Main Menu";
	_state = ACTIVE;

	_nextMenuY = 0;

    cout << "MenuScreen constructor complete\n";
}

MenuScreen::~MenuScreen()
{
    //TODO: Rewrite for new MenuEntry class

    //dtor
    list<MenuEntry *>::iterator it;
    MenuEntry * tempEntry;

    for(it = _entryList.begin(); it != _entryList.end(); it++)
    {
        tempEntry = (*it);
        delete tempEntry;
    }


}

void MenuScreen::handleInput(InputManager * input)
{
    //TODO: Edit for new MenuEntry class and derivatives

	int sizeEntry;
	list<MenuEntry *>::iterator it;
	sizeEntry = _entryList.size() - 1;
	int x;
	MenuButton * testButton = NULL;
    int mouseX, mouseY;

	// Only make a change if the key was just pressed, not held down

	// Down key
	if(input->keyPressed(SDLK_DOWN) || input->keyPressed(SDLK_s))
	{
		_menuSelect++;
		if (_menuSelect > sizeEntry)
			_menuSelect = 0;
		// skip disabled entries

		it = _entryList.begin();
		for(x=0;x<_menuSelect;x++)
            it++;

		while((*it)->getEnabled() == false)
		{
			_menuSelect++;
			it++;
			if (_menuSelect > sizeEntry)
            {
                _menuSelect = 0;
                it = _entryList.begin();
            }

		}
	}

	// Up key
	if(input->keyPressed(SDLK_UP) || input->keyPressed(SDLK_w))
	{
		_menuSelect--;
		if (_menuSelect < 0)
			_menuSelect = sizeEntry;

        it = _entryList.begin();
		for(x=0;x<_menuSelect;x++)
            it++;

		while((*it)->getEnabled() == false)
		{
			_menuSelect--;
			it--;

			if (_menuSelect < 0)
            {
				_menuSelect = sizeEntry;
				it = _entryList.end();
				it--;
            }

		}
	}

	// Enter key
	if(input->keyPressed(SDLK_RETURN))
	{
        it = _entryList.begin();
		for(x=0;x<_menuSelect;x++)
            it++;
        _selectedEntry = (*it);
        testButton = dynamic_cast<MenuButton *>(_selectedEntry);
        if (testButton != NULL) // it's a MenuButton
            testButton->runCallback();
	}

	if(input->mousePressed(SDL_BUTTON_LEFT))
    {
        input->mouseLocation(mouseX, mouseY);

        cout << "Mouse clicked at X: " << mouseX << "  Y: " << mouseY << endl;



        if (mouseX > _menuRect.x && mouseX <= (_menuRect.w + _menuRect.x) && mouseY > _menuRect.y && mouseY <= (_menuRect.h + _menuRect.y))
        {
            cout << "Clicked within menu. Bounds- X: " << _menuRect.x << " - " << _menuRect.w << "  Y: " << _menuRect.y << " - " << _menuRect.h << endl;

            it = _entryList.begin();
            for(it=_entryList.begin();it!=_entryList.end();++it)
            {
                _selectedEntry = (*it);
                if(_selectedEntry->mouseOver(mouseX, mouseY))
                {
                    _selectedEntry->onMousePress();
                    _lastClickedEntry = _selectedEntry;
                }

            }
        }

    }

    if(input->mouseReleased(SDL_BUTTON_LEFT))
    {
        input->mouseLocation(mouseX, mouseY);

        cout << "Mouse released at X: " << mouseX << "  Y: " << mouseY << endl;

        if (mouseX > _menuRect.x && mouseX <= (_menuRect.w + _menuRect.x) && mouseY > _menuRect.y && mouseY <= (_menuRect.h + _menuRect.y))
        {
            cout << "Released within menu. Bounds- X: " << _menuRect.x << " - " << _menuRect.w << "  Y: " << _menuRect.y << " - " << _menuRect.h << endl;

            it = _entryList.begin();
            for(it=_entryList.begin();it!=_entryList.end();++it)
            {
                _selectedEntry = (*it);
                if(_selectedEntry->mouseOver(mouseX, mouseY) && _selectedEntry == _lastClickedEntry)
                {
                    _selectedEntry->runCallback();
                    _selectedEntry->onMouseExit();
                    _lastClickedEntry = NULL;
                }
                else
                {
                    _selectedEntry->onMouseExit();
                }

            }
        }
        else // Mouse released outside menu
        {
            // Reset all the buttons with onMouseExit
            for(it=_entryList.begin();it!=_entryList.end();++it)
            {
                _selectedEntry = (*it);
                _selectedEntry->onMouseExit();
            }


        }
    }


}

void MenuScreen::update()
{

}

/*
SDL_Surface * MenuScreen::draw()
{
    return NULL;
}*/

void MenuScreen::draw(SDL_Renderer * gRen)
{
	list<MenuEntry *>::iterator it;

	for(it = _entryList.begin(); it != _entryList.end(); it++)
	{
		(*it)->draw(gRen);
	}

}


void MenuScreen::unload()
{
	_state = SHUTDOWN;
}

void MenuScreen::addMenuEntry(MenuEntry * entry)
{
    // TODO: Rewrite for new MenuEntry class

    cout << "addMenuEntry() started\n";
    _entryList.push_back(entry);
    cout << "addMenuEntry() complete\n";
}

/*
void MenuScreen::addMenuEntry(bool enable, std::string menuName, TTF_Font * fnt, SDL_Rect rect, SDL_Renderer * ren)
{
    // TODO: Rewrite for new MenuEntry class

    MenuEntry * entry;
    SDL_Color txtColor;
    cout << "addMenuEntry() started\n";

    txtColor.r = 255;
    txtColor.g = 255;
    txtColor.b = 255;
    entry = new MenuEntry(rect.x, rect.y + _nextMenuY, rect.w, rect.h);

    entry->setEnabled(enable);
    entry->setText(menuName);
    entry->_texture.setFont(fnt);
    entry->_texture.setRenderer(ren);
    entry->_texture.loadFromRenderedText(entry->getText(), txtColor);

    _entryList.push_back(entry);
    cout << "addMenuEntry() complete\n";
}
*/

void MenuScreen::setBackground(std::string bkgndFile)
{
    _bkgrndTexture.loadFromFile(bkgndFile);
}

/*
MenuEntry * MenuScreen::getChosen()
{
    //TODO: Rewrite for MenuEntry callbacks

    MenuEntry * tempEntry;

    tempEntry = _selectedEntry;
    _selectedEntry = NULL;
    return tempEntry;
}
*/
