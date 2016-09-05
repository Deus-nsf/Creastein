
#include "cl_PlafondBase.hpp"



PlafondBase::PlafondBase(CustomForme* _Forme) : CustomObject(_Forme)
{

}


PlafondBase::PlafondBase(CustomForme* _Forme, D3DXVECTOR3& _TranVector)
	:CustomObject(_Forme, _TranVector)
{

}


PlafondBase::PlafondBase(CustomForme* _Forme, D3DXVECTOR3& _TranVector, D3DXVECTOR3& _LocalRotVector, D3DXVECTOR3& _GlobalRotVector)
	:CustomObject(_Forme, _TranVector, _LocalRotVector, _GlobalRotVector)
{

}


PlafondBase::~PlafondBase()
{

}


void PlafondBase::SpecialActions()
{

}


void PlafondBase::ObjectRendering()
{
	// applique les parametres de texture
	poForme->SetTextureParameters();

	// applique la transformation geometrique
	GeoTransform();

	// render of plane
	poForme->RenderingOfObject();
}