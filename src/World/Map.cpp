#include "Map.h"

MapBase::MapBase(int w, int h, int sX, int sY, Globals * glbls)
{
    //ctor
    width = w;
    height = h;
    startX = sX;
    startY = sY;

    globals = glbls;

    tileList = new Tile *[width];

    for( int i = 0 ; i < width ; i++ )
        tileList[i] = new Tile[height];

	tempMapSetup();


}

MapBase::~MapBase()
{
    //dtor
    for( int i = 0 ; i < width ; i++ )
        delete [] tileList[i] ;
    delete [] tileList ;
}

SDL_Rect MapBase::getTileSource(TileType TType)
{
    SDL_Rect sRect;

    switch(TType)
    {
    case GRASS:
        sRect.x = 0;
        sRect.y = 0;
        sRect.w = 32;
        sRect.h = 32;
        break;
    case WATER:
        sRect.x = 0;
        sRect.y = 32;
        sRect.w = 32;
        sRect.h = 32;
        break;
    case FOOTHILL:
        sRect.x = 0;
        sRect.y = 64;
        sRect.w = 32;
        sRect.h = 32;
        break;
    case MOUNTAIN:
        sRect.x = 0;
        sRect.y = 96;
        sRect.w = 32;
        sRect.h = 32;
        break;
    default:
        sRect.x = 0;
        sRect.y = 0;
        sRect.w = 32;
        sRect.h = 32;
        break;
    }
    return sRect;
}

void MapBase::tempMapSetup()
{
	int x, y;

	// Temporary map
	for(x = 0;x < width;x++)
		for(y = 0;y < height;y++)
		{
			tileList[x][y].terrainType = WATER;
			tileList[x][y].tileGFX = globals->getTexture("MapTiles");
			tileList[x][y].aniFrame = 0;
			tileList[x][y].isBlocked = true;
		}

    // Map border

	for(x = 0;x < width;x++)
    {
        tileList[x][0].terrainType = MOUNTAIN;
        tileList[x][0].tileGFX = globals->getTexture("MapTiles");
        tileList[x][0].aniFrame = 0;
        tileList[x][0].isBlocked = true;
        tileList[x][height-1].terrainType = MOUNTAIN;
        tileList[x][height-1].tileGFX = globals->getTexture("MapTiles");
        tileList[x][height-1].aniFrame = 0;
        tileList[x][height-1].isBlocked = true;
    }
    for(y = 0;y < height;y++)
    {
        tileList[0][y].terrainType = MOUNTAIN;
        tileList[0][y].tileGFX = globals->getTexture("MapTiles");
        tileList[0][y].aniFrame = 0;
        tileList[0][y].isBlocked = true;
        tileList[width-1][y].terrainType = MOUNTAIN;
        tileList[width-1][y].tileGFX = globals->getTexture("MapTiles");
        tileList[width-1][y].aniFrame = 0;
        tileList[width-1][y].isBlocked = true;
    }

	// Simple Island
	for(x = 22;x <= 33;x++)
		for(y = 22;y <= 31;y++)
			tileList[x][y].terrainType = GRASS;


	tileList[27][25].terrainType = FOOTHILL;
	tileList[28][25].terrainType = FOOTHILL;
	tileList[27][24].terrainType = FOOTHILL;
	tileList[28][26].terrainType = MOUNTAIN;

	// Get Tile source rectangles
	for(x = 0;x < width;x++)
		for(y = 0;y < height;y++)
		{
			tileList[x][y].SrcRect = getTileSource(tileList[x][y].terrainType);
		}
}
