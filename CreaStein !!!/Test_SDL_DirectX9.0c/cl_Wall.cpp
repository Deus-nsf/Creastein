
#include "cl_Wall.hpp"



Wall::Wall(CustomForme* _Forme) : CustomObject(_Forme)
{
	
}


Wall::Wall(CustomForme* _Forme, D3DXVECTOR3& _TranVector)
	:CustomObject(_Forme, _TranVector)
{
	
}


Wall::Wall(CustomForme* _Forme, D3DXVECTOR3& _TranVector, D3DXVECTOR3& _LocalRotVector, D3DXVECTOR3& _GlobalRotVector)
	:CustomObject(_Forme, _TranVector, _LocalRotVector, _GlobalRotVector)
{
	
}


Wall::~Wall()
{

}


void Wall::GeoActions()
{
	// renseigne les vecteurs rotations
	//SetLocalRotation(0.0f, fRot/16, 0.0f);
	//SetGlobalRotation(0.0f, fRot/8, 0.0f);
}


void Wall::SpecialActions()
{

}


void Wall::ObjectRendering()
{
	// applique les parametres de texture
	poForme->SetTextureParameters();

	// applique la transformation geometrique
	GeoTransform();

	// render of cube
	poForme->RenderingOfObject();
}