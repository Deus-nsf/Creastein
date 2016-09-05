
#pragma once

#include "header_ressources.hpp"
#include "cl_CustomObject.hpp"


class Wall : public CustomObject
{
protected:
	float fRot;

public:
	Wall(CustomForme* _Forme);
	Wall(CustomForme* _Forme, D3DXVECTOR3& _TranVector);
	Wall(CustomForme* _Forme, D3DXVECTOR3& _TranVector, D3DXVECTOR3& _LocalRotVector, D3DXVECTOR3& _GlobalRotVector);
	~Wall();

	virtual void GeoActions();
	virtual void SpecialActions();
	virtual void ObjectRendering();
};