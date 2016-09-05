
#include "cl_Joueur.hpp"


Joueur::Joueur()
{
	Speed.x = 0.2f;
	Speed.y = 0.2f;
	Speed.z = 0.0f;

	bCours = false;
	iPtsDeVie = 100;
	iNbrPrismes = 0;
}


Joueur::~Joueur()
{

}




D3DXVECTOR3* Joueur::GetSpeed()
{
	return &Speed;
}


void Joueur::SetSpeed(D3DXVECTOR3* _NewSpeed)
{
	Speed = *_NewSpeed;
}




bool Joueur::GetCours()
{
	return bCours;
}


void Joueur::SetCours(bool _bCours)
{
	bCours = _bCours;
}




int Joueur::GetPtsDeVie()
{
	return iPtsDeVie;
}


void Joueur::SetPtsDeVie(int _NbrPtsDeVie)
{
	iPtsDeVie = _NbrPtsDeVie;
}


void Joueur::PrendsCher(int _Damages)
{
	iPtsDeVie -= _Damages;
}


void Joueur::RefaisUneSante(int _Heal)
{
	iPtsDeVie += _Heal;
}




int Joueur::GetNbrPrismes()
{
	return iNbrPrismes;
}


void Joueur::SetNbrPrismes(int _NbrPrismes)
{
	iNbrPrismes = _NbrPrismes;
}


void Joueur::GagneUnPrisme()
{
	++iNbrPrismes;
}


void Joueur::PerdsUnPrisme()
{
	--iNbrPrismes;
}