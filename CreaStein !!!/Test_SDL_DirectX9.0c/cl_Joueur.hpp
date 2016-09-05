
#pragma once

#include "header_ressources.hpp"


class Joueur
{
private:
	D3DXVECTOR3 Speed;
	bool bCours;
	int iPtsDeVie;
	int iNbrPrismes;

public:
	Joueur();
	~Joueur();

	D3DXVECTOR3* GetSpeed();
	void SetSpeed(D3DXVECTOR3*);

	bool GetCours();
	void SetCours(bool);
	

	int GetPtsDeVie();
	void SetPtsDeVie(int);
	void PrendsCher(int);
	void RefaisUneSante(int);

	int GetNbrPrismes();
	void SetNbrPrismes(int);
	void GagneUnPrisme();
	void PerdsUnPrisme();
};