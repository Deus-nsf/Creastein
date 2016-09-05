
#include "cl_CustomCube.hpp"



CustomCube::CustomCube(CustomForme* _Forme) : CustomObject(_Forme)
{
	fRot = 0.0f;
}


CustomCube::CustomCube(CustomForme* _Forme, D3DXVECTOR3& _TranVector)
	:CustomObject(_Forme, _TranVector)
{
	fRot = 0.0f;
}


CustomCube::CustomCube(CustomForme* _Forme, D3DXVECTOR3& _TranVector, D3DXVECTOR3& _LocalRotVector, D3DXVECTOR3& _GlobalRotVector)
	:CustomObject(_Forme, _TranVector, _LocalRotVector, _GlobalRotVector)
{
	fRot = 0.0f;
}


CustomCube::~CustomCube()
{

}



void CustomCube::GeoActions()
{
	/*// renseigne les vecteurs rotations
	SetLocalRotation(fRot/16, 0.0f, 0.0f);
	SetGlobalRotation(0.0f, fRot/8, 0.0f);

	fRot += 0.05f;*/
}


void CustomCube::SpecialActions()
{

}


void CustomCube::ObjectRendering()
{
	// applique les parametres de texture
	poForme->SetTextureParameters();

	// applique la transformation geometrique
	GeoTransform();

	// render of form
	poForme->RenderingOfObject();
}