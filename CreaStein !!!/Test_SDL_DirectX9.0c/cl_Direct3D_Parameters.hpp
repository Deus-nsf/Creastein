
#pragma once

#include "header_ressources.hpp"


struct D3DVERTEX
{
	float fX,fY,fZ;
	DWORD dwColor;
};

struct D3DVERTEX_TEX
{
	float fX,fY,fZ;
	float fU,fV;
};

#define CUSTOM_FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define CUSTOM_FVF_TEXMAPPING (D3DFVF_XYZ | D3DFVF_TEX1)


#define HEXA_BLACK 0x00000000
#define HEXA_WHITE 0xffffffff
#define HEXA_RED 0xffff0000
#define HEXA_GREEN 0xff00ff00
#define HEXA_BLUE 0xff0000ff
#define HEXA_YELLOW 0xffffff00


class Direct3D_Parameters
{
private:
	Direct3D_Parameters();

public :
	LPDIRECT3D9				 Direct3D_object;		 //used to create a direct 3d device
	LPDIRECT3DDEVICE9		 Direct3D_device;
	D3DPRESENT_PARAMETERS	 present_parameters;
	D3DXMATRIX				 projection_matrix;
	D3DXMATRIX				 matView;				 //pour la camera
	VOID* pData;									 //pointer to beginning of vertex buffer
	RECT Screen;

	static Direct3D_Parameters* GetSingleton();
	~Direct3D_Parameters();

	void InitD3D();

	void CreateD3D_Object();
	void SetDeviceParameters();
	void CreateD3D_Device();
	void SetStates();
};