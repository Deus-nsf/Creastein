
#include "cl_CustomObject.hpp"



// objet de base
CustomObject::CustomObject(CustomForme* _Forme)
{
	D3DXMatrixIdentity(&LocalTranMatrix);
	D3DXMatrixIdentity(&TranMatrix);
	D3DXMatrixIdentity(&LocalRotMatrix);
	D3DXMatrixIdentity(&GlobalRotMatrix);

	D3D_Para = Direct3D_Parameters::GetSingleton();
	poForme = _Forme;
	LocalTranVector = TranVector = LocalRotVector = GlobalRotVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bPorteActivee = false;
	bBlocker = true;
}


// objet avec une position connue
CustomObject::CustomObject(CustomForme* _Forme, D3DXVECTOR3& _TranVector)
{
	D3DXMatrixIdentity(&LocalTranMatrix);
	D3DXMatrixIdentity(&TranMatrix);
	D3DXMatrixIdentity(&LocalRotMatrix);
	D3DXMatrixIdentity(&GlobalRotMatrix);

	D3D_Para = Direct3D_Parameters::GetSingleton();
	poForme = _Forme;
	TranVector = _TranVector;
	LocalTranVector = LocalRotVector = GlobalRotVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bPorteActivee = false;
	bBlocker = true;
}


// objet avec une position et des rotation connues
CustomObject::CustomObject(CustomForme* _Forme, D3DXVECTOR3& _TranVector, D3DXVECTOR3& _LocalRotVector, D3DXVECTOR3& _GlobalRotVector)
{
	D3DXMatrixIdentity(&LocalTranMatrix);
	D3DXMatrixIdentity(&TranMatrix);
	D3DXMatrixIdentity(&LocalRotMatrix);
	D3DXMatrixIdentity(&GlobalRotMatrix);

	D3D_Para = Direct3D_Parameters::GetSingleton();
	poForme = _Forme;
	TranVector = _TranVector;
	LocalRotVector = _LocalRotVector;
	GlobalRotVector = _GlobalRotVector;

	LocalTranVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bPorteActivee = false;
	bBlocker = true;
}


CustomObject::~CustomObject()
{

}


CustomForme* CustomObject::GetpoForme()
{
	return poForme;
}


void CustomObject::SetXLocalPosition(float fLocPosX)
{
	LocalTranVector.x = fLocPosX;
}


void CustomObject::SetPosition(D3DXVECTOR3* _TranVector)
{
	TranVector = *_TranVector;
}


void CustomObject::SetPosition(float fPosX, float fPosY, float fPosZ)
{
	TranVector.x = fPosX;
	TranVector.y = fPosY;
	TranVector.z = fPosZ;
}


void CustomObject::SetXPosition(float fPosX)
{
	TranVector.x = fPosX;
}


void CustomObject::SetYPosition(float fPosY)
{
	TranVector.y = fPosY;
}


void CustomObject::SetZPosition(float fPosZ)
{
	TranVector.z = fPosZ;
}



float CustomObject::GetXPosition() const
{
	return TranVector.x;
}


float CustomObject::GetYPosition() const
{
	return TranVector.y;
}


float CustomObject::GetZPosition() const
{
	return TranVector.z;
}




void CustomObject::SetLocalRotation(D3DXVECTOR3* _RotVector)
{
	LocalRotVector = *_RotVector;
}


void CustomObject::SetLocalRotation(float fRotX, float fRotY, float fRotZ)
{
	LocalRotVector.x = fRotX;
	LocalRotVector.y = fRotY;
	LocalRotVector.z = fRotZ;
}



void CustomObject::SetGlobalRotation(D3DXVECTOR3* _RotVector)
{
	GlobalRotVector = *_RotVector;
}


void CustomObject::SetGlobalRotation(float fRotX, float fRotY, float fRotZ)
{
	GlobalRotVector.x = fRotX;
	GlobalRotVector.y = fRotY;
	GlobalRotVector.z = fRotZ;
}


void CustomObject::GeoActions()
{

}


void CustomObject::GeoTransform()
{
	D3DXMatrixTranslation(&LocalTranMatrix, LocalTranVector.x, LocalTranVector.z, LocalTranVector.z);
	D3DXMatrixRotationYawPitchRoll(&LocalRotMatrix, LocalRotVector.y, LocalRotVector.x, LocalRotVector.z);	// Attention à l'ordre !
	D3DXMatrixRotationYawPitchRoll(&GlobalRotMatrix, GlobalRotVector.y, GlobalRotVector.x, GlobalRotVector.z);	// Attention à l'ordre !
	D3DXMatrixTranslation(&TranMatrix, TranVector.x, TranVector.y, TranVector.z);

	// applique les transformations geometriques dans un ordre bien particulier qui me permet par exemple de decaler un objet
	// avant de le faire tourner comme je le veux, puis le positionne sur la scene.
	D3D_Para->Direct3D_device->SetTransform(D3DTS_WORLD, &(LocalTranMatrix * LocalRotMatrix * GlobalRotMatrix * /*Global*/TranMatrix));
}