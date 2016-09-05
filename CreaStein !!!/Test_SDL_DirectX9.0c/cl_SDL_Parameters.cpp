
#include "cl_SDL_Parameters.hpp"


SDL_Parameters::SDL_Parameters()
{
	ecran = NULL;
	SDL_EnableKeyRepeat(0, 0);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	// TOUJOURS APRES SDL_Init !!!!!!!!!!!!!
	SDL_EnableUNICODE(1);

	fTempsPrecGeo = fTempsPrecEvents = fTempsPrecRender = fTempsActuel = SDL_GetTicks();
	keystate = SDL_GetKeyState(NULL);

	GetWindowRect(GetDesktopWindow(), &Screen);
}


SDL_Parameters* SDL_Parameters::GetSingleton()
{
	static SDL_Parameters oSDL_Parameters;
	return &oSDL_Parameters;
}


SDL_Parameters::~SDL_Parameters()
{
	SDL_Quit();
}


void SDL_Parameters::InitWindow()
{
	ecran = SDL_SetVideoMode(Screen.right, Screen.bottom, SDL_GetVideoInfo()->vfmt->BitsPerPixel, SDL_NOFRAME);
	SDL_ShowCursor(0);
}

// methode abandonée
void SDL_Parameters::FixSDLFullscreenBug()
{
	/*ecran = SDL_SetVideoMode(Screen.right, Screen.bottom, SDL_GetVideoInfo()->vfmt->BitsPerPixel, SDL_FULLSCREEN);*/
}