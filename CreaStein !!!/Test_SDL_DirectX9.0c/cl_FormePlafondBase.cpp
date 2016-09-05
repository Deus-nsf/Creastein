
#include "cl_FormePlafondBase.hpp"


FormePlafondBase::FormePlafondBase() : CustomForme()
{
	Plane_buffer = NULL;
}


FormePlafondBase::~FormePlafondBase()
{

}


// creation d'un plane de 200/200/200 metres
void FormePlafondBase::SetForms()
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


void FormePlafondBase::CreateVertexBuffers()
{
	D3D_Para->Direct3D_device->CreateVertexBuffer(sizeof(aPlane), D3DUSAGE_WRITEONLY, CUSTOM_FVF_TEXMAPPING, 
														D3DPOOL_MANAGED, &Plane_buffer, NULL);
}


void FormePlafondBase::FeedVertexBuffers()
{
	for(int i = 0; i < 6; ++i)
	{
		Plane_buffer->Lock(0, sizeof(D3D_Para->pData), (void**)&D3D_Para->pData, 0);
		memcpy(D3D_Para->pData, aPlane, sizeof(aPlane));
		Plane_buffer->Unlock();
	}
}



void FormePlafondBase::SetTextureParameters()
{
	// change le type de Vertex
	D3D_Para->Direct3D_device->SetFVF(CUSTOM_FVF_TEXMAPPING);

	D3D_Para->Direct3D_device->SetTexture(0, pObjectTexture);
}


void FormePlafondBase::LoadTextureForObject()
{
	D3DXCreateTextureFromFile(D3D_Para->Direct3D_device,
                          "../Textures/plafond_base_tex.png",
                          &pObjectTexture);
}


void FormePlafondBase::RenderingOfObject()
{
	for(int i = 0; i < 6; ++i)
	{
		D3D_Para->Direct3D_device->SetStreamSource(0, Plane_buffer, 0, sizeof(D3DVERTEX_TEX));
		D3D_Para->Direct3D_device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}