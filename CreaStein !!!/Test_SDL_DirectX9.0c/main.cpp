
#include "cl_Game.hpp"



int main(int argc, char *argv[])
{
	Game* oGame = Game::GetSingleton();
	oGame->InitializeSDL_D3D();

	return EXIT_SUCCESS;
}