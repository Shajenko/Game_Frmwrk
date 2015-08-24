#include "TitleScreen.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/Window.h>
#include <CEGUI/WindowManager.h>


TitleScreen::TitleScreen(unsigned int x, unsigned int y, unsigned int w, unsigned int h) : BaseScreen(x, y, w, h)
{
    std::cout << "Creating TitleScreen\n";

	_name = "Title Screen";
	_state = ACTIVE;

    _mState = MAIN_MENU;

	_smallFont = new Font(12, "./res/arial.ttf");
	_largeFont = new Font(30, "./res/arial.ttf");

	_mainMenu = nullptr;
	_optionsMenu = nullptr;
	_volumeMenu = nullptr;

	_musicVol = nullptr;
	_soundEffVol = nullptr;

	_backgrndTex = new Texture("./gfx/GradientBrown640480.jpg", GL_RGBA);
	_testTex = new Texture("./gfx/GradientGray640480.jpg", GL_RGBA);

	std::cout << "Title Screen constructor complete\n";
}


TitleScreen::~TitleScreen()
{
	//dtor
	delete _backgrndTex;
}

void TitleScreen::handleInput(InputManager * inputM)
{
	// Menu input
	if(_mState == MAIN_MENU);
//        _mMenu->handleInput(inputM);
    else if(_mState == OPTIONS_MENU);
//        _optionsMenu->handleInput(inputM);
    else if(_mState == VOLUME_MENU);
//        _volumeMenu->handleInput(inputM);

}

void TitleScreen::update()
{
	//Flash effect

	// Increment animation time
	_ticks++;

	if (_ticks % 3 == 0)
	{
		_r = (rand() % 160 + 40) / 256.0f;
		_g = (rand() % 160 + 40) / 256.0f;
		_b = (rand() % 160 + 40) / 256.0f;
		_ticks = 1;
	}

    if(_mState == MAIN_MENU)
    {
    }
    else if(_mState == OPTIONS_MENU)
    {

    }
	else if (_mState == VOLUME_MENU)
	{

	}
	else // something went wrong
	{
		_mState == MAIN_MENU;
		activateMenu(_mainMenu);
	}

}

void TitleScreen::draw(RenderEngine * rEngine)
{
	rEngine->drawSprite(_testTex, glm::vec4(30.0f, 50.0f, 100.0f, 500.0f));
	rEngine->drawSprite(_backgrndTex, glm::vec4(_x * 1.0f, _y * 1.0f, _w * 1.0f, _h * 1.0f));
	

	rEngine->drawString("Welcome to", glm::vec3(20.0f, 40.0f, 0.0f), _smallFont, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	rEngine->drawString("PONG", glm::vec3(60.0f, 100.0f, 0.0f), _largeFont, glm::vec4(_r, _g, _b, 1.0f));

	return;

}



void TitleScreen::unload()
{
    _state = SHUTDOWN;
}

void TitleScreen::createGUIElements()
{
	using namespace CEGUI;

	int i;
	size_t childCount;


	// Create GUI elements
	_mainMenu = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("MainMenu.layout"); // ./../CEGUI/

	childCount = _mainMenu->getChildCount();

	for (i = 0; i < childCount; i++)
	{
		// Register all buttons with function buttonPress
		_mainMenu->getChildAtIdx(i)->subscribeEvent(
			PushButton::EventClicked,    // If we recall our button was of type CEGUI::PushButton in the .scheme
			// and we want to acknowledge the EventClicked action.
			Event::Subscriber(           // What function to call when this is clicked.  Remember, all functions 
			// are contained within (this) class.
			&TitleScreen::buttonPress,				// Call buttonPress member of TitleScreen
			this));                             // Using (this) instance we're in right now
	}

	_optionsMenu = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("OptionsMenu.layout"); // ./../CEGUI/
	childCount = _optionsMenu->getChildCount();

	for (i = 0; i < childCount; i++)
	{
		// Register all buttons with function buttonPress
		_optionsMenu->getChildAtIdx(i)->subscribeEvent(
			PushButton::EventClicked,    // If we recall our button was of type CEGUI::PushButton in the .scheme
			// and we want to acknowledge the EventClicked action.
			Event::Subscriber(           // What function to call when this is clicked.  Remember, all functions 
			// are contained within (this) class.
			&TitleScreen::buttonPress,				// Call buttonPress member of TitleScreen
			this));                             // Using (this) instance we're in right now
	}

	_volumeMenu = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("VolumeMenu.layout");
	_volumeMenu->getChild("ReturnOptButton")->subscribeEvent(
		PushButton::EventClicked,    // If we recall our button was of type CEGUI::PushButton in the .scheme
		// and we want to acknowledge the EventClicked action.
		Event::Subscriber(           // What function to call when this is clicked.  Remember, all functions 
		// are contained within (this) class.
		&TitleScreen::buttonPress,				// Call buttonPress member of TitleScreen
		this));                             // Using (this) instance we're in right now

	_musicVol = static_cast<Slider *>(_volumeMenu->getChild("MusicVol"));
	if (_musicVol == nullptr)
		std::cout << "Failed to convert MusicVol slider\n";
	_soundEffVol = static_cast<Slider *>(_volumeMenu->getChild("SoundEffVol"));
	if (_soundEffVol == nullptr)
		std::cout << "Failed to convert SoundEffVol slider\n";

	//_musicVol->setCurrentValue(0.5f);
	//_soundEffVol->setCurrentValue(0.5f);


	_optionsMenu->hide();
	_volumeMenu->hide();

	_rEngine->addCEGUIElement(_mainMenu);
	_rEngine->addCEGUIElement(_optionsMenu);
	_rEngine->addCEGUIElement(_volumeMenu);
}



// Menu functions

bool TitleScreen::buttonPress(const CEGUI::EventArgs& e)
{
	// Figure out which button was pressed from the event args
	const CEGUI::WindowEventArgs* args = static_cast<const CEGUI::WindowEventArgs*>(&e);

	CEGUI::String name = args->window->getName();

	std::cout << name << " was pressed\n";

	if (name == "NewGameButton")
	{
		MessageBox(NULL, "New Game", "New Game Chosen", MB_OK);
	}
	else if (name == "ContinueGameButton")
	{
		MessageBox(NULL, "Continue Game", "Continue Game Chosen", MB_OK);
	}
	else if (name == "OptionsButton")
	{

		_mainMenu->hide();

		activateMenu(_optionsMenu);   // bug:  No effect - problem with loading options menu?
		_mState = OPTIONS_MENU;
	}
	else if (name == "CreditsButton")
	{
		MessageBox(NULL, "Credits", "Credits Chosen", MB_OK);
	}
	else if (name == "ExitButton")
	{
		SDL_Event * quitEvent;
		quitEvent = new SDL_Event;
		quitEvent->type = SDL_QUIT;
		SDL_PushEvent(quitEvent);
	}
	else if (name == "ControlsButton")
	{
		MessageBox(NULL, "Controls", "Controls Chosen", MB_OK);
	}
	else if (name == "GraphicsButton")
	{
		MessageBox(NULL, "Graphics", "Graphics Chosen", MB_OK);
	}
	else if (name == "ReturnButton")
	{
		_optionsMenu->hide();

		activateMenu(_mainMenu);

		_mState = MAIN_MENU;
	}
	else if (name == "VolumeButton")
	{
		_optionsMenu->hide();
		_mainMenu->hide();

		activateMenu(_volumeMenu);

		_mState = VOLUME_MENU;
		//MessageBox(NULL, "Volume", "Volume Chosen", MB_OK);
	}
	else if (name == "ReturnOptButton")
	{
		_volumeMenu->hide();

		activateMenu(_optionsMenu);

		_mState = OPTIONS_MENU;
	}
	else // default case
	{
		MessageBox(NULL, "Another button was pressed", "Error", MB_OK);
		return false;
	}
	return true;

}

void TitleScreen::activateMenu(CEGUI::Window * menu)
{
	menu->show();
	menu->activate();
}