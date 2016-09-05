
#include "cl_Game.hpp"


Game::Game()
{
	bContinuer = true;
	SDL_Para = SDL_Parameters::GetSingleton();
	D3D_Para = Direct3D_Parameters::GetSingleton();
	fStabilisation = (float)1/INPUTRATE;
	SDL_GetMouseState(&iPosSourisX, &iPosSourisY);
	SDL_GetMouseState(&iPosSourisXPrec, &iPosSourisYPrec);

	fSensivSouris = 0.002f;
}


Game* Game::GetSingleton()
{
	static Game oGame;
	return &oGame;
}


Game::~Game()
{
	while (Map.size() > 0)
	{
		while (Map.back()->size() > 0)
		{
			Map.back()->pop_back();
		}

		Map.pop_back();
	}

	while (SolPlafond.size() > 0)
	{
		SolPlafond.pop_back();
	}

	while (ListOfForms.size() > 0)
	{
		ListOfForms.pop_back();
	}
}



void Game::InitializeSDL_D3D()
{
	SDL_Para->InitWindow();
	D3D_Para->InitD3D();
	CreateForms();
	ReadCreateMap();
	GameLoop();
}



void Game::CreateForms()
{
	// NE SURTOUT PAS OUBLIER DE CREER LES RESSOURCES POUR LES FORMES APRES LES AVOIR ALLOUES

	/*E_Cube,
	E_Pyramide,
	E_Door,
	E_PlafondBase,
	E_SolPierre,
	E_Wall,*/

	ListOfForms.push_back( new FormeCube );
	ListOfForms.back()->CreateRessourcesForObject();

	ListOfForms.push_back( new FormePyramide );
	ListOfForms.back()->CreateRessourcesForObject();

	ListOfForms.push_back( new FormeDoor );
	ListOfForms.back()->CreateRessourcesForObject();

	ListOfForms.push_back( new FormePlafondBase );
	ListOfForms.back()->CreateRessourcesForObject();

	ListOfForms.push_back( new FormeSolPierre );
	ListOfForms.back()->CreateRessourcesForObject();

	ListOfForms.push_back( new FormeWall );
	ListOfForms.back()->CreateRessourcesForObject();
}



void Game::ReadCreateMap()
{
	char ChaineUtilitaire[200] = {0};
	char cValeurMap = ' ';
	int iTailleMapY = 50;
	int iTailleMapX = 100;
	FILE* pFluxNiveau = fopen("../Files/map.txt", "r");

	while (cValeurMap  != '*')
	{
		cValeurMap = fgetc(pFluxNiveau);
	}

	
	for (int y = iTailleMapY; y > 0; --y)
	{
		Map.push_back(new MapX);

		for(int iLoops = 0; iLoops < y; ++iLoops)
		{
			//passe a la ligne suivante
			fgets(ChaineUtilitaire, 200, pFluxNiveau);
		}

		for (int x = 0; x < iTailleMapX; ++x)
		{
			cValeurMap = fgetc(pFluxNiveau);

			switch( cValeurMap )
			{
			case 'P':	// Prisme
				Map.back()->push_back( new CustomPyramide(ListOfForms[E_Pyramide], D3DXVECTOR3(1.0f + (x * 2.0f), 1.0f, 1.0f + ((iTailleMapY - y) * 2.0f) ) ));
				break;

			case 'D':	// Door orientee normale
				Map.back()->push_back( new Door(ListOfForms[E_Door], D3DXVECTOR3(1.0f + (x * 2.0f), 1.5f, 1.0f + ((iTailleMapY - y) * 2.0f) ) ));
				break;

			case 'Y':	// Door tournee
				Map.back()->push_back( new Door(ListOfForms[E_Door], D3DXVECTOR3(1.0f + (x * 2.0f), 1.5f, 1.0f + ((iTailleMapY - y) * 2.0f) ),
																	D3DXVECTOR3(0.0f, 3.141592f/2.0f, 0.0f),
																	D3DXVECTOR3(0.0f, 0.0f, 0.0f) ));
				break;

			case 'W':	// Wall
				Map.back()->push_back( new Wall(ListOfForms[E_Wall], D3DXVECTOR3(1.0f + (x * 2.0f), 2.0f, 1.0f + ((iTailleMapY - y) * 2.0f) ) ));
				break;

			default :
				Map.back()->push_back(NULL);
				break;
			}
		}

		rewind(pFluxNiveau);

		while (cValeurMap  != '*')
		{
			cValeurMap = fgetc(pFluxNiveau);
		}
	}

	SolPlafond.push_back( new SolPierre(ListOfForms[E_SolPierre], D3DXVECTOR3((float)iTailleMapX, 0.0f, (float)iTailleMapY)) );
	SolPlafond.push_back( new PlafondBase(ListOfForms[E_PlafondBase], D3DXVECTOR3((float)iTailleMapX, 4.0f, (float)iTailleMapY)) );

	fclose(pFluxNiveau);
}



void Game::GameLoop()
{
	while (bContinuer)
	{
		// recuperation du temps actuel depuis l'execution du programme
		SDL_Para->fTempsActuel = SDL_GetTicks();

		// gestion des actions géometriques (et pas transformations hein, actions) à "GEORATE" units/secondes
		if ( (SDL_Para->fTempsActuel - SDL_Para->fTempsPrecGeo) >= 1000/GEORATE )
		{
			GeoActionsLoop();

			SDL_Para->fTempsPrecGeo = SDL_Para->fTempsActuel;
		}

		// gestion d'inputs à "INPUTRATE" units/secondes
		if ( (SDL_Para->fTempsActuel - SDL_Para->fTempsPrecEvents) >= 1000/INPUTRATE )
		{
			EventsLoop();
			DetecterPrisme();
			SDL_Para->fTempsPrecEvents = SDL_Para->fTempsActuel;
		}

		// affichage à "FRAMERATE" units/secondes
		if ( (SDL_Para->fTempsActuel - SDL_Para->fTempsPrecRender) >= 1000/FRAMERATE )	
		{
			Render();
			SDL_Para->fTempsPrecRender = SDL_Para->fTempsActuel;
		}
	}
}


void Game::GeoActionsLoop()
{
	for (unsigned int j = 0; j < Map.size(); ++j)
	{
		for (unsigned int i = 0; i < Map[j]->size(); ++i)
		{
			if(Map.at(j)->at(i) != NULL)
			{
				Map.at(j)->at(i)->SpecialActions();
				Map.at(j)->at(i)->GeoActions();
			}
		}
	}

	for (unsigned int i = 0; i < SolPlafond.size(); ++i)
	{
		SolPlafond[i]->SpecialActions();
		SolPlafond[i]->GeoActions();
	}
}


void Game::EventsLoop()
{
	D3DXVECTOR3 VecPosition;
	D3DXVECTOR3 VecLook;
	D3DXVECTOR3 VecRight;
	D3DXVECTOR3 CiblePuzzle;


	// recuperation des positions de la souris pour la position precedente
	SDL_GetMouseState(&iPosSourisXPrec, &iPosSourisYPrec);
	
	while( SDL_PollEvent( &SDL_Para->event ) )
	{
		// recuperation des positions de la souris pour la position actuelle
		SDL_GetMouseState(&iPosSourisX, &iPosSourisY);
		oCamFPS.yaw((iPosSourisX - iPosSourisXPrec) * fSensivSouris);

		// on recalle la souris au centre de l'ecran, selon la resolution de l'utilisateur
		SDL_WarpMouse((Uint16)D3D_Para->Screen.right/2, (Uint16)D3D_Para->Screen.bottom/2);

		switch ( SDL_Para->event.type )
		{
		case SDL_QUIT:
			bContinuer = 0;
			break;
		case SDL_KEYDOWN:
			switch ( SDL_Para->event.key.keysym.unicode )
			{
			case SDLK_ESCAPE:
				bContinuer = 0;
				break;
			case SDLK_e:
				oCamFPS.getPosition(&VecPosition);
				oCamFPS.getLook(&VecLook);
				VecLook.x *= 2.5f;
				VecLook.z *= 2.5f;
				D3DXVec3Add(&CiblePuzzle, &VecPosition, &VecLook);
				CiblePuzzle.x = (float) ((int)CiblePuzzle.x/2);
				CiblePuzzle.z = (float) ((int)CiblePuzzle.z/2);

				if(Map.at((unsigned int)CiblePuzzle.z)->at((unsigned int)CiblePuzzle.x) != NULL)
				{
					if(oJoueur.GetNbrPrismes() > 0)
					{
						Map.at((unsigned int)CiblePuzzle.z)->at((unsigned int)CiblePuzzle.x)->bPorteActivee = true;
						oJoueur.PerdsUnPrisme();
					}
				}
				break;
			}			
			break;
		}
	}

	if ( SDL_Para->keystate[SDLK_LSHIFT] )
	{
		oJoueur.SetCours( true );
	}
	else
	{
		oJoueur.SetCours( false );
	}

	if ( oJoueur.GetCours() )
	{
		oJoueur.SetSpeed( &D3DXVECTOR3(0.1f, 0.0f, 0.3f) );	// vit strafe/ nothing/ vit walk
	}
	else
	{
		oJoueur.SetSpeed( &D3DXVECTOR3(0.1f, 0.0f, 0.15f) );
	}

	// clavier americain obligatoire... pas de compatibilité unicode
	if ( SDL_Para->keystate[SDLK_d] )
	{
		oCamFPS.getPosition(&VecPosition);
		oCamFPS.getRight(&VecRight);
		D3DXVec3Add(&CiblePuzzle, &VecPosition, &VecRight);
		CiblePuzzle.x = (float) ((int)CiblePuzzle.x/2);
		CiblePuzzle.z = (float) ((int)CiblePuzzle.z/2);

		oCamFPS.strafe(oJoueur.GetSpeed()->x);

		if(Map.at((unsigned int)CiblePuzzle.z)->at((unsigned int)CiblePuzzle.x) != NULL)
		{
			if(Map.at((unsigned int)CiblePuzzle.z)->at((unsigned int)CiblePuzzle.x)->bBlocker == true)
			{
				oCamFPS.strafe(-oJoueur.GetSpeed()->x);
			}
		}
	}
			
	if ( SDL_Para->keystate[SDLK_a] )
	{
		oCamFPS.getPosition(&VecPosition);
		oCamFPS.getRight(&VecRight);
		D3DXVec3Subtract(&CiblePuzzle, &VecPosition, &VecRight);
		CiblePuzzle.x = (float) ((int)CiblePuzzle.x/2);
		CiblePuzzle.z = (float) ((int)CiblePuzzle.z/2);

		oCamFPS.strafe(-oJoueur.GetSpeed()->x);

		if(Map.at((unsigned int)CiblePuzzle.z)->at((unsigned int)CiblePuzzle.x) != NULL)
		{
			if(Map.at((unsigned int)CiblePuzzle.z)->at((unsigned int)CiblePuzzle.x)->bBlocker == true)
			{
				oCamFPS.strafe(oJoueur.GetSpeed()->x);
			}
		}
	}

	if ( SDL_Para->keystate[SDLK_w] )
	{
		oCamFPS.getPosition(&VecPosition);
		oCamFPS.getLook(&VecLook);
		D3DXVec3Add(&CiblePuzzle, &VecPosition, &VecLook);
		CiblePuzzle.x = (float) ((int)CiblePuzzle.x/2);
		CiblePuzzle.z = (float) ((int)CiblePuzzle.z/2);

		oCamFPS.walk(oJoueur.GetSpeed()->z);

		if(Map.at((unsigned int)CiblePuzzle.z)->at((unsigned int)CiblePuzzle.x) != NULL)
		{
			if(Map.at((unsigned int)CiblePuzzle.z)->at((unsigned int)CiblePuzzle.x)->bBlocker == true)
			{
				oCamFPS.walk(- oJoueur.GetSpeed()->z);
			}
		}
	}

	if ( SDL_Para->keystate[SDLK_s] )
	{
		oCamFPS.getPosition(&VecPosition);
		oCamFPS.getLook(&VecLook);
		D3DXVec3Subtract(&CiblePuzzle, &VecPosition, &VecLook);
		CiblePuzzle.x = (float) ((int)CiblePuzzle.x/2);
		CiblePuzzle.z = (float) ((int)CiblePuzzle.z/2);

		oCamFPS.walk(- (oJoueur.GetSpeed()->z/1.8f));

		if(Map.at((unsigned int)CiblePuzzle.z)->at((unsigned int)CiblePuzzle.x) != NULL)
		{
			if(Map.at((unsigned int)CiblePuzzle.z)->at((unsigned int)CiblePuzzle.x)->bBlocker == true)
			{
				oCamFPS.walk((oJoueur.GetSpeed()->z/1.8f));
			}
		}
	}
}


void Game::DetecterPrisme()
{
	D3DXVECTOR3 VecPosition;
	oCamFPS.getPosition(&VecPosition);

	VecPosition.x = (float) ((int)VecPosition.x/2);
	VecPosition.z = (float) ((int)VecPosition.z/2);

	if(Map.at((unsigned int)VecPosition.z)->at((unsigned int)VecPosition.x) != NULL)
	{
		if(Map.at((unsigned int)VecPosition.z)->at((unsigned int)VecPosition.x)->GetpoForme() == ListOfForms[E_Pyramide])
		{
			Map.at((unsigned int)VecPosition.z)->at((unsigned int)VecPosition.x) = NULL;
			oJoueur.GagneUnPrisme();
		}
	}
}


void Game::Render()
{
	// camera
	D3DXMATRIX M_view;
	oCamFPS.getViewMatrix(&M_view);
	D3D_Para->Direct3D_device->SetTransform(D3DTS_VIEW, &M_view) ;

	// Clear buffers
	D3D_Para->Direct3D_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
										D3DCOLOR_XRGB(0,0,0), 1.0f, 0);

	// RENDERING OF OBJECTS //
	D3D_Para->Direct3D_device->BeginScene();

	for (unsigned int j = 0; j < Map.size(); ++j)
	{
		for (unsigned int i = 0; i < Map[j]->size(); ++i)
		{
			if(Map.at(j)->at(i) != NULL)
			{
				Map.at(j)->at(i)->ObjectRendering();
			}
		}
	}

	for (unsigned int i = 0; i < SolPlafond.size(); ++i)
	{
		SolPlafond[i]->ObjectRendering();
	}

	D3D_Para->Direct3D_device->EndScene();
	// END OF RENDERING	//

	// swap back/front buffers
	D3D_Para->Direct3D_device->Present(NULL, NULL, NULL, NULL);
}



void Game::Desinitialize()
{
	D3D_Para->Direct3D_device->Release();
	D3D_Para->Direct3D_device = NULL;
	D3D_Para->Direct3D_object->Release();
	D3D_Para->Direct3D_object = NULL;
}