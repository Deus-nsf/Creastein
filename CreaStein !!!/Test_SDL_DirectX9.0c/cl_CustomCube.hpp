
#pragma once

#include "header_ressources.hpp"
#include "cl_CustomObject.hpp"


class CustomCube : public CustomObject
{
protected:
	float fRot;

public:
	CustomCube(CustomForme* _Forme);
	CustomCube(CustomForme* _Forme, D3DXVECTOR3& _TranVector);
	CustomCube(CustomForme* _Forme, D3DXVECTOR3& _TranVector, D3DXVECTOR3& _LocalRotVector, D3DXVECTOR3& _GlobalRotVector);
	~CustomCube();

	virtual void GeoActions();
	virtual void SpecialActions();
	virtual void ObjectRendering();
};