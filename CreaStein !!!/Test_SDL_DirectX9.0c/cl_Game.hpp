
#pragma once

#include "header_classes.hpp"


// on peut gerer independemment actions geometriques auto, inputs pris en compte, et images affichés,
// chaque parametre est sa valeur / secondes
#define GEORATE 60	// permet d'accelerer ou ralentir les transformations géometriques auto (rotations auto sur un objet par exemple)
#define INPUTRATE 60	// evitez de depasser 60, car il y a une limite d'inputs pris en compte par la SDL et au dela le calcul de fStabilisation risque d'etre faussé
#define FRAMERATE 60	// à mettre a 120 pour les ecrans 120 Hz par exemple


enum LIST_OF_FORMS
{
	E_Cube,
	E_Pyramide,
	E_Door,
	E_PlafondBase,
	E_SolPierre,
	E_Wall,

	E_NbrFormes,
};


enum LIST_OF_OBJECTS
{
	E_ObjCube,
	E_ObjPyramide,
	E_ObjDoor,
	E_ObjPlafondBase,
	E_ObjSolPierre,
	E_ObjWall,

	E_NbrObjets,
};


typedef std::vector<CustomObject *> MapX;


class Game
{
private:
	Game();

	bool bContinuer;
	SDL_Parameters* SDL_Para;
	Direct3D_Parameters* D3D_Para;
	CameraFPS oCamFPS;
	Joueur oJoueur;
	
	int iPosSourisXPrec, iPosSourisYPrec;
	int iPosSourisX, iPosSourisY;

	float fSensivSouris;

	// permet de garder la meme vitesse pour les actions influencés par des inputs
	// indépendemment de l'INPUTRATE
	float fStabilisation;

	std::vector<CustomForme *> ListOfForms;
	std::vector<MapX*> Map;

	std::vector<CustomObject *> SolPlafond;

public:
	static Game* GetSingleton();
	~Game();

	void InitializeSDL_D3D();
	void CreateForms();
	void ReadCreateMap();

	void GameLoop();

	void GeoActionsLoop();
	void EventsLoop();
	void DetecterPrisme();
	void Render();

	void Desinitialize();
};