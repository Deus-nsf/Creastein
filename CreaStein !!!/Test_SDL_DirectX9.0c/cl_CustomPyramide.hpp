
#pragma once

#include "header_ressources.hpp"
#include "cl_CustomObject.hpp"


class CustomPyramide : public CustomObject
{
protected :
	float fRot;

public:
	CustomPyramide(CustomForme* _Forme);
	CustomPyramide(CustomForme* _Forme, D3DXVECTOR3& _TranVector);
	CustomPyramide(CustomForme* _Forme, D3DXVECTOR3& _TranVector, D3DXVECTOR3& _LocalRotVector, D3DXVECTOR3& _GlobalRotVector);
	~CustomPyramide();

	virtual void GeoActions();
	virtual void SpecialActions();
	virtual void ObjectRendering();
};