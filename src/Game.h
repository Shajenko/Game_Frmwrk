#ifndef GAME_H
#define GAME_H

#include "Globals.h"

#include "./gfx/ScreenManager.h"
#include "Initialization.h"

#include <GL/glew.h> // needs to be before "SDL_opengl.h
#include <GL/glu.h>


#include <iostream>

class Game
{
    public:
        Game();
        ~Game();
        int run();
    protected:
    private:
        Globals * _globals;
        ScreenManager * _scrManager;
};

#endif // GAME_H
