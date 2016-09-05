
#pragma once

#include "header_ressources.hpp"
#include "cl_CustomObject.hpp"


class SolPierre : public CustomObject
{

public:
	SolPierre(CustomForme* _Forme);
	SolPierre(CustomForme* _Forme, D3DXVECTOR3& _TranVector);
	SolPierre(CustomForme* _Forme, D3DXVECTOR3& _TranVector, D3DXVECTOR3& _LocalRotVector, D3DXVECTOR3& _GlobalRotVector);
	~SolPierre();

	virtual void SpecialActions();
	virtual void ObjectRendering();
};