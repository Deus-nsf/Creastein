
#include "cl_Door.hpp"


Door::Door(CustomForme* _Forme) : CustomObject(_Forme)
{
	fAvancementPorte = 0.0f;
}


Door::Door(CustomForme* _Forme, D3DXVECTOR3& _TranVector)
	:CustomObject(_Forme, _TranVector)
{
	fAvancementPorte = 0.0f;
}


Door::Door(CustomForme* _Forme, D3DXVECTOR3& _TranVector, D3DXVECTOR3& _LocalRotVector, D3DXVECTOR3& _GlobalRotVector)
	:CustomObject(_Forme, _TranVector, _LocalRotVector, _GlobalRotVector)
{
	fAvancementPorte = 0.0f;
}



Door::~Door()
{

}



void Door::GeoActions()
{
	/*
	// renseigne les vecteurs rotations
	SetGlobalRotation(0.0f, fRot/8, 0.0f);

	fRot += 0.05f;*/
}


void Door::SpecialActions()
{
	if (fAvancementPorte >= 2.0f)
	{
		bPorteActivee = false;
		bBlocker = false;
	}

	if (bPorteActivee == true)
	{
		fAvancementPorte += 0.03f;
		SetXLocalPosition(fAvancementPorte);
	}
}


void Door::ObjectRendering()
{
	// applique les parametres de texture
	poForme->SetTextureParameters();

	// applique la transformation geometrique
	GeoTransform();

	// render of cube
	poForme->RenderingOfObject();
}