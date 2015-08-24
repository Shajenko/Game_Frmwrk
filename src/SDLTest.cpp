#include "Globals.h"

#include "Game.h"

int main( int argc, char* args[] )
{
    Game * gm;

    gm = new Game();

    gm->run();

    return 0;
}
