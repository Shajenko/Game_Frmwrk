#include "MainMenu.h"

#include <string>
using namespace std;
#include <Windows.h>

MainMenu::MainMenu(unsigned int x, unsigned int y, unsigned int w, unsigned int h, Globals * globals, ScreenManager * scrnmgr) : MenuScreen(x, y, w, h, globals, scrnmgr)
{

	Uint32 rmask, gmask, bmask, amask;

	string menuNames[4] = {"New Game", "Continue Game", "Options", "Credits"};

	cout << "Main Menu constructor\n";

	//ctor
	menuRect.x = x;
	menuRect.y = y;
	menuRect.w = w;
	menuRect.h = h;

	menuSelect = 0;

	name = "Main Menu";
	state = ACTIVE;

	setGlobals(globals);

	// Add entries

	addEntries(menuNames[0], true);
	addEntries(menuNames[1], false);
	addEntries(menuNames[2], true);
	addEntries(menuNames[3], true);



    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

	tempSurf = SDL_CreateRGBSurface(SDL_SWSURFACE, menuRect.w, menuRect.h, 32,
                                   rmask, gmask, bmask, amask);

    scrn = SDL_ConvertSurface(tempSurf, tempSurf->format, tempSurf->flags);



    // todo: Create each of the menu entries as a texture
    // Clear buffer
	//	SDL_BlitSurface(tempSurf, NULL, txtScreen, &txtRect);
    // Write menu
	//	txtScreen = TTF_RenderText_Solid(globals->getFont("Arial 28"), menuText.c_str(), txtColor);

    cout << "Main Menu constructor complete\n";

}

void MainMenu::createTextures(SDL_Renderer * gRen)
{
    cout << "Main Menu createTextures()\n";
    SDL_Color txtColor;
//	SDL_Rect txtRect;
	list<MenuEntry *>::iterator it;
	MenuEntry * tempEntry;
	string menuText = "Test";

    txtColor.r = 255;
    txtColor.g = 255;
    txtColor.b = 255;


    // Create each menu entry with white text

    for(it = entries.begin(); it != entries.end(); ++it)
	{
	    tempEntry = (*it);
        menuText = tempEntry->text;

		// Clear buffer
//		SDL_BlitSurface(tempSurf, NULL, txtScreen, &txtRect);
		// Write menu
		tempEntry->texture.setRenderer(gRen);
		tempEntry->texture.setFont(globals->getFont("Arial 28"));
		tempEntry->texture.loadFromRenderedText(menuText.c_str(), txtColor);

		// Add texture to list

//		entryTextures.push_back(tempTexture);
	}

	bkgrndTexture = SDL_CreateTextureFromSurface(gRen, tempSurf);
}

MainMenu::~MainMenu()
{
	//dtor
}

void MainMenu::addEntries(string text, bool enabled)
{
	MenuEntry * entry;
	entry = new MenuEntry;
	entry->enabled = enabled;
	entry->text = text;

	entries.push_back(entry);
}

void MainMenu::handleInput(InputManager * input)
{

	int sizeEntry;
	list<MenuEntry *>::iterator it;
	sizeEntry = entries.size() - 1;
	int x;

	// Only make a change if the key was just pressed, not held down

	// Down key
	if(input->keyPressed(SDLK_DOWN) || input->keyPressed(SDLK_s))
	{
		menuSelect++;
		if (menuSelect > sizeEntry)
			menuSelect = 0;
		// skip disabled entries

		it = entries.begin();
		for(x=0;x<menuSelect;x++)
            it++;

		while((*it)->enabled == false)
		{
			menuSelect++;
			it++;
			if (menuSelect > sizeEntry)
            {
                menuSelect = 0;
                it = entries.begin();
            }

		}
	}

	// Up key
	if(input->keyPressed(SDLK_UP) || input->keyPressed(SDLK_w))
	{
		menuSelect--;
		if (menuSelect < 0)
			menuSelect = sizeEntry;

        it = entries.begin();
		for(x=0;x<menuSelect;x++)
            it++;

		while((*it)->enabled == false)
		{
			menuSelect--;
			it--;

			if (menuSelect < 0)
            {
				menuSelect = sizeEntry;
				it = entries.end();
				it--;
            }

		}
	}

	// Enter key
	if(input->keyPressed(SDLK_RETURN))
		switch(menuSelect)
		{
			case NEW_GAME: // New Game
				// New Game Response
                screenMngr->unloadScreen("Title Screen");
                screenMngr->unloadScreen("Main Menu");
//				screenMngr->addScreen(new TableScreen(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, globals));
                unload();
				break;
			case CONTINUE_GAME: // Continue Game
				// Continue Game Response
				MessageBox(NULL, "Continue Game!", "Continue Game", MB_OK);
				break;
			case OPTIONS:
				// Options Response
				MessageBox(NULL, "Options!", "Options", MB_OK);
				break;
			case CREDITS:
				// Credits Response
				MessageBox(NULL, "Credits!", "Credits", MB_OK);
				break;
			default:
				break;
		}
}

void MainMenu::update()
{

}

SDL_Surface * MainMenu::draw()
{
	SDL_Color txtColor;
	SDL_Surface * txtScreen;
	int menuY = 20;
	SDL_Rect txtRect, menuEntryRect;
	list<MenuEntry *>::iterator it;
	MenuEntry * tempEntry;
	string menuText = "Test";



	int x;

    it = entries.begin();

	// Draw menu graphics (background and such)

	menuEntryRect.x = 0;
	menuEntryRect.y = 0;
	menuEntryRect.w = menuRect.w;
	menuEntryRect.h = menuRect.h;

	SDL_BlitSurface(tempSurf, NULL, scrn, &menuEntryRect);

	// Draw menu options

	txtRect.x = 0;
	txtRect.y = 0;
	txtRect.w = menuRect.w;
	txtRect.h = 40;

	x=0;

    // Update mingw to properly debug

	for(it = entries.begin(); it != entries.end(); ++it)
	{
	    tempEntry = (*it);
        menuText = tempEntry->text;

		if(x == menuSelect)
		{
			txtColor.r = 255;
			txtColor.g = 0;
			txtColor.b = 0;
		}
		else if(!tempEntry->enabled)
		{
			txtColor.r = 150;
			txtColor.g = 150;
			txtColor.b = 150;
		}
		else
		{
			txtColor.r = 255;
			txtColor.g = 255;
			txtColor.b = 255;
		}

		menuEntryRect.x = 20;
		menuEntryRect.y = menuY;
		menuEntryRect.w = menuRect.w - 20;
		menuEntryRect.h = 40;

		menuY += 40;



		// Clear buffer
		SDL_BlitSurface(tempSurf, NULL, txtScreen, &txtRect);
		// Write menu
		txtScreen = TTF_RenderText_Solid(globals->getFont("Arial 28"), menuText.c_str(), txtColor);
		//Blit to main screen
		SDL_BlitSurface(txtScreen, NULL, scrn, &menuEntryRect);

		x++;
	}

	return scrn;
}

void MainMenu::draw(SDL_Renderer * gRen)
{
    // todo: copy each prerender texture into the correct spots, modified for color
   	SDL_Color txtColor;
	int menuY;
	SDL_Rect menuEntryRect;
	list<MenuEntry *>::iterator it;
	MenuEntry * tempEntry;
	string menuText = "Test";



	int x;

    menuY = menuRect.h / 4;

    it = entries.begin();

	// Draw menu graphics (background and such)

	menuEntryRect.x = menuRect.x;
	menuEntryRect.y = menuRect.y;
	menuEntryRect.w = menuRect.w;
	menuEntryRect.h = menuRect.h;

/*	SDL_RenderCopy(gRen, bkgrndTexture, NULL, &menuEntryRect);

	SDL_BlitSurface(tempSurf, NULL, scrn, &menuEntryRect);*/

	x=0;

    // Update mingw to properly debug

	for(it = entries.begin(); it != entries.end(); ++it)
	{
	    tempEntry = (*it);
        menuText = tempEntry->text;

		if(x == menuSelect)
		{
			txtColor.r = 255;
			txtColor.g = 0;
			txtColor.b = 0;
		}
		else if(!tempEntry->enabled)
		{
			txtColor.r = 150;
			txtColor.g = 150;
			txtColor.b = 150;
		}
		else
		{
			txtColor.r = 255;
			txtColor.g = 255;
			txtColor.b = 255;
		}

		menuEntryRect.y += menuY;

        menuEntryRect.x = menuRect.x;
        menuEntryRect.w = menuRect.w - 20;
        menuEntryRect.h = menuY - 10;

        tempEntry->texture.setColor(txtColor.r, txtColor.g, txtColor.b);

        // Render texture to screen
        tempEntry->texture.render(menuEntryRect.x, menuEntryRect.y);

		x++;
	}

}

void MainMenu::unload()
{
    state = SHUTDOWN;
}
