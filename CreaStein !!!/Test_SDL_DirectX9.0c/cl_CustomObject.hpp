
#pragma once

#include "header_ressources.hpp"
#include "cl_Direct3D_Parameters.hpp"
#include "cl_CustomForme.hpp"


class CustomObject
{
protected:
	Direct3D_Parameters* D3D_Para;

	// pointeur sur ma forme
	CustomForme* poForme;

	// translation and rotations matrix for geometric transformations
	D3DXMATRIX LocalTranMatrix;
	D3DXMATRIX TranMatrix;	// global, la fleme de tout renommer -_-
	D3DXMATRIX LocalRotMatrix;
	D3DXMATRIX GlobalRotMatrix;

	// position values (meters) and rotations values (radiants) of object
	D3DXVECTOR3 LocalTranVector;
	D3DXVECTOR3 TranVector;	// global, la fleme de tout renommer -_-
	D3DXVECTOR3 LocalRotVector;
	D3DXVECTOR3 GlobalRotVector;

public:
	CustomObject(CustomForme* _Forme);
	CustomObject(CustomForme* _Forme, D3DXVECTOR3& _TranVector);	// pour set la position d'origine d'un objet
	CustomObject(CustomForme* _Forme, D3DXVECTOR3& _TranVector, D3DXVECTOR3& _LocalRotVector, D3DXVECTOR3& _GlobalRotVector); // pour set la position et les rotations classiques d'origine d'un objet
	~CustomObject();

	bool bPorteActivee;
	bool bBlocker;

	virtual void GeoActions();
	virtual void SpecialActions() = 0;
	void GeoTransform();

	CustomForme* GetpoForme();
	
	void SetXLocalPosition(float fLocPosX);

	void SetPosition(D3DXVECTOR3*);
	void SetPosition(float fPosX, float fPosY, float fPosZ);

	void SetXPosition(float fPosX);
	void SetYPosition(float fPosY);
	void SetZPosition(float fPosZ);

	float GetXPosition() const; 
	float GetYPosition() const; 
	float GetZPosition() const; 

	void SetLocalRotation(D3DXVECTOR3*);
	void SetLocalRotation(float fRotX, float fRotY, float fRotZ);

	void SetGlobalRotation(D3DXVECTOR3*);
	void SetGlobalRotation(float fRotX, float fRotY, float fRotZ);

	virtual void ObjectRendering() = 0;
};