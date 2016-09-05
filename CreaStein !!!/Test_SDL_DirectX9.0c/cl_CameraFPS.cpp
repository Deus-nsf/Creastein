
#include "cl_CameraFPS.hpp"


CameraFPS::CameraFPS()
{
	_pos   = D3DXVECTOR3(4.0f, 2.0f, 49.0f);
	_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	_up    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	_look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}

CameraFPS::CameraFPS(CameraFPS& _Cam)
{
	_pos   = _Cam._pos;
	_right = _Cam._right;
	_up    = _Cam._up;
	_look  = _Cam._look;
}

CameraFPS::~CameraFPS()
{

}

void CameraFPS::getPosition(D3DXVECTOR3* pos)
{
	*pos = _pos;
}

void CameraFPS::setPosition(D3DXVECTOR3* pos)
{
	_pos = *pos;
}

void CameraFPS::getRight(D3DXVECTOR3* right)
{
	*right = _right;
}

void CameraFPS::getUp(D3DXVECTOR3* up)
{
	*up = _up;
}

void CameraFPS::getLook(D3DXVECTOR3* look)
{
	*look = _look;
}



void CameraFPS::strafe(float units)
{
	// move only on xz plane for land object
	_pos += D3DXVECTOR3(_right.x, 0.0f, _right.z) * units;

}

void CameraFPS::fly(float units)
{
	// move only on y-axis for land object
	_pos.y += units;
}

void CameraFPS::walk(float units)
{
	// move only on xz plane for land object
	D3DXVECTOR3 v(_look.x, 0.0f, _look.z);

	if (D3DXVec3Length(&v) == 0.0f)
		v = _up;

	D3DXVec3Normalize(&v, &v);

	_pos += v * units;
}


void CameraFPS::yaw(float angle)
{
	D3DXMATRIX T;

	// rotate around world y (0, 1, 0) always for land object
	D3DXMatrixRotationY(&T, angle);

	// rotate _right and _look around _up or y-axis
	D3DXVec3TransformCoord(&_right,&_right, &T);
	D3DXVec3TransformCoord(&_look,&_look, &T);
	D3DXVec3TransformCoord(&_up,&_up, &T);
}

void CameraFPS::roll(float angle)
{
	// no roll
}

void CameraFPS::pitch(float angle)
{
	// no pitch
}


void CameraFPS::getViewMatrix(D3DXMATRIX* V)
{
	// Keep camera's axes orthogonal to each other
	D3DXVec3Normalize(&_look, &_look);

	D3DXVec3Cross(&_up, &_look, &_right);
	D3DXVec3Normalize(&_up, &_up);

	D3DXVec3Cross(&_right, &_up, &_look);
	D3DXVec3Normalize(&_right, &_right);

	// Build the view matrix:
	float x = -D3DXVec3Dot(&_right, &_pos);
	float y = -D3DXVec3Dot(&_up, &_pos);
	float z = -D3DXVec3Dot(&_look, &_pos);

	(*V)(0,0) = _right.x; (*V)(0, 1) = _up.x; (*V)(0, 2) = _look.x; (*V)(0, 3) = 0.0f;
	(*V)(1,0) = _right.y; (*V)(1, 1) = _up.y; (*V)(1, 2) = _look.y; (*V)(1, 3) = 0.0f;
	(*V)(2,0) = _right.z; (*V)(2, 1) = _up.z; (*V)(2, 2) = _look.z; (*V)(2, 3) = 0.0f;
	(*V)(3,0) = x;        (*V)(3, 1) = y;     (*V)(3, 2) = z;       (*V)(3, 3) = 1.0f;
}

void CameraFPS::update(float timeDelta)
{

}