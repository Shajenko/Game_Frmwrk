#ifndef TILE_H
#define TILE_H

#include "../Constants.h"

enum TileType {GRASS, WATER, FOOTHILL, MOUNTAIN };

struct Tile
{
    public:
        TileType terrainType;
        SDL_Surface * tileGFX;
        SDL_Rect SrcRect;
        int locationX;
        int locationY;
        int aniFrame;

        // Tile actions
        bool isActivated;
        bool isBlocked;
        bool isTouchTrigger;
        bool isStepTrigger;
};

#endif // TILE_H
