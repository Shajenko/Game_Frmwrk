#include "Globals.h"

Globals::Globals()
{
	srand(time(NULL));
}

Globals::~Globals()
{
	// Delete all textures
	// Delete all fonts
}

int Globals::randomNumber(int maximum)
{
	return rand() % maximum;
}
