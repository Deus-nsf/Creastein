
#pragma once

#include "header_ressources.hpp"


class SDL_Parameters
{
private:
	SDL_Parameters();

	// permet d'obtenir la res du bureau
	RECT Screen;

public:
	SDL_Event event;
	SDL_Surface *ecran;
	Uint32 fTempsActuel, fTempsPrecRender, fTempsPrecEvents, fTempsPrecGeo;
	Uint8 *keystate;
	
	static SDL_Parameters* GetSingleton();
	~SDL_Parameters();

	void InitWindow();
	void FixSDLFullscreenBug();
};