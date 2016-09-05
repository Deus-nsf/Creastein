
#pragma once

#include "header_ressources.hpp"
#include "cl_CustomObject.hpp"


class Door : public CustomObject
{
protected:
	float fAvancementPorte;

public:
	Door(CustomForme* _Forme);
	Door(CustomForme* _Forme, D3DXVECTOR3& _TranVector);
	Door(CustomForme* _Forme, D3DXVECTOR3& _TranVector, D3DXVECTOR3& _LocalRotVector, D3DXVECTOR3& _GlobalRotVector);
	~Door();

	virtual void GeoActions();
	virtual void SpecialActions();
	virtual void ObjectRendering();
};