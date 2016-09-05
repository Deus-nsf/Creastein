
#include "cl_CustomPyramide.hpp"



CustomPyramide::CustomPyramide(CustomForme* _Forme) : CustomObject(_Forme)
{
	fRot = 0.0f;
	bBlocker = false;
}


CustomPyramide::CustomPyramide(CustomForme* _Forme, D3DXVECTOR3& _TranVector)
	:CustomObject(_Forme, _TranVector)
{
	fRot = 0.0f;
	bBlocker = false;
}


CustomPyramide::CustomPyramide(CustomForme* _Forme, D3DXVECTOR3& _TranVector, D3DXVECTOR3& _LocalRotVector, D3DXVECTOR3& _GlobalRotVector)
	:CustomObject(_Forme, _TranVector, _LocalRotVector, _GlobalRotVector)
{
	fRot = 0.0f;
	bBlocker = false;
}


CustomPyramide::~CustomPyramide()
{

}


void CustomPyramide::GeoActions()
{
	// renseigne les vecteurs rotations
	SetLocalRotation(0.0f, -fRot, 0.0f);
	//SetGlobalRotation(fRot/8, 0.0f, 0.0f);

	fRot += 0.04f;
}


void CustomPyramide::SpecialActions()
{

}


void CustomPyramide::ObjectRendering()
{
	// change le type de Vertex
	D3D_Para->Direct3D_device->SetFVF(CUSTOM_FVF);

	// applique les parametres de texture
	poForme->SetTextureParameters();

	// applique la transformation geometrique
	GeoTransform();

	// render of pyramide
	poForme->RenderingOfObject();
}