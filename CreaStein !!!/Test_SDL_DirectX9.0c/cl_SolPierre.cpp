
#include "cl_SolPierre.hpp"



SolPierre::SolPierre(CustomForme* _Forme) : CustomObject(_Forme)
{

}


SolPierre::SolPierre(CustomForme* _Forme, D3DXVECTOR3& _TranVector)
	:CustomObject(_Forme, _TranVector)
{

}


SolPierre::SolPierre(CustomForme* _Forme, D3DXVECTOR3& _TranVector, D3DXVECTOR3& _LocalRotVector, D3DXVECTOR3& _GlobalRotVector)
	:CustomObject(_Forme, _TranVector, _LocalRotVector, _GlobalRotVector)
{

}


SolPierre::~SolPierre()
{

}



void SolPierre::SpecialActions()
{

}


void SolPierre::ObjectRendering()
{
	// applique les parametres de texture
	poForme->SetTextureParameters();

	// applique la transformation geometrique
	GeoTransform();

	// render of cube
	poForme->RenderingOfObject();
}