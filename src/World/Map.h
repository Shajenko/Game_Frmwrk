#ifndef MAP_H
#define MAP_H

#include "..\Constants.h"
#include "..\Globals.h"
#include "Tile.h"


class MapBase
{
    public:
        MapBase(int, int, int, int, Globals *);
        virtual ~MapBase();
        SDL_Rect getTileSource(TileType TType);
        void tempMapSetup();
        Tile * getTile(int x, int y) {return &tileList[x][y];}
    protected:
    private:
        Tile ** tileList;
        int width, height;
        int startX, startY;
        Globals * globals;
};

#endif // MAP_H
