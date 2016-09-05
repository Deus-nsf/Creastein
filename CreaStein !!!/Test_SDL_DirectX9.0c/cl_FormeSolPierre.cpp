
#include "cl_FormeSolPierre.hpp"


FormeSolPierre::FormeSolPierre() : CustomForme()
{
	Plane_buffer = NULL;
}


FormeSolPierre::~FormeSolPierre()
{

}


// creation d'un plane de 200/0/100 metres
void FormeSolPierre::SetForms()
{
	// arranged as triangle strips
	D3DVERTEX_TEX VertexArray[4] = {{-100.0f,  0.0f, -50.0f,		0.0f, 0.0f}, //1. plane
									{-100.0f,  0.0f,  50.0f,		0.0f, 50.0f},
									{ 100.0f,  0.0f, -50.0f,		100.0f, 0.0f},
									{ 100.0f,  0.0f,  50.0f,		100.0f, 50.0f}};

										 
	for(int i = 0; i < 4; ++i)
	{
		aPlane[i] = VertexArray[i];
	}
}


void FormeSolPierre::CreateVertexBuffers()
{
	D3D_Para->Direct3D_device->CreateVertexBuffer(sizeof(aPlane), D3DUSAGE_WRITEONLY, CUSTOM_FVF_TEXMAPPING, 
														D3DPOOL_MANAGED, &Plane_buffer, NULL);
}


void FormeSolPierre::FeedVertexBuffers()
{
	for(int i = 0; i < 6; ++i)
	{
		Plane_buffer->Lock(0, sizeof(D3D_Para->pData), (void**)&D3D_Para->pData, 0);
		memcpy(D3D_Para->pData, aPlane, sizeof(aPlane));
		Plane_buffer->Unlock();
	}
}



void FormeSolPierre::SetTextureParameters()
{
	// change le type de Vertex
	D3D_Para->Direct3D_device->SetFVF(CUSTOM_FVF_TEXMAPPING);

	D3D_Para->Direct3D_device->SetTexture(0, pObjectTexture);
}


void FormeSolPierre::LoadTextureForObject()
{
	D3DXCreateTextureFromFile(D3D_Para->Direct3D_device,
                          "../Textures/sol_pierre_tex.png",
                          &pObjectTexture);
}


void FormeSolPierre::RenderingOfObject()
{
	for(int i = 0; i < 6; ++i)
	{
		D3D_Para->Direct3D_device->SetStreamSource(0, Plane_buffer, 0, sizeof(D3DVERTEX_TEX));
		D3D_Para->Direct3D_device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}