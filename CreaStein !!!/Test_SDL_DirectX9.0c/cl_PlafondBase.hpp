
#pragma once

#include "header_ressources.hpp"
#include "cl_CustomObject.hpp"


class PlafondBase : public CustomObject
{

public:
	PlafondBase(CustomForme* _Forme);
	PlafondBase(CustomForme* _Forme, D3DXVECTOR3& _TranVector);
	PlafondBase(CustomForme* _Forme, D3DXVECTOR3& _TranVector, D3DXVECTOR3& _LocalRotVector, D3DXVECTOR3& _GlobalRotVector);
	~PlafondBase();

	virtual void SpecialActions();
	virtual void ObjectRendering();
};