#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

/*
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <GL/glew.h> // needs to be before "SDL_opengl.h
#include <GL/glu.h>
#include "SDL_opengl.h"

#include <list>
#include <vector>
#include <iostream>
#include <ctime>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <string>
*/

//The attributes of the screen
const float SCREEN_WIDTH = 800.0f;
const float SCREEN_HEIGHT = 600.0f;
const int SCREEN_BPP = 32;
const int MAX_FRAMES = 60;

enum ScreenState { ACTIVE, HIDDEN, SHUTDOWN};

#endif // CONSTANTS_H_INCLUDED
