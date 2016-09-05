
#include "cl_FormeDoor.hpp"


FormeDoor::FormeDoor() : CustomForme()
{
	for(int i = 0; i < 2; ++i)
		SixQuadArray_buffer[i] = NULL;
}


FormeDoor::~FormeDoor()
{

}



// creation d'un pave de 2/3/0.2 metres
void FormeDoor::SetForms()
{
	// arranged as triangle strips
	D3DVERTEX_TEX ArrayOfVertexArrays[6][4] = {{{ -1.0f, -1.5f, -0.1f,		0.0f, 1.0f}, //1. quad
												 {-1.0f,  1.5f, -0.1f,		0.0f, 0.0f},
												 { 1.0f, -1.5f, -0.1f,		1.0f, 1.0f},
												 { 1.0f,  1.5f, -0.1f,		1.0f, 0.0f}},

												 {{ 1.0f, -1.5f, -0.1f,		0.0f, 1.0f}, //1. quad
												 { 1.0f,  1.5f, -0.1f,		0.0f, 0.0f},
												 { 1.0f, -1.5f,  0.1f,		1.0f, 1.0f},
												 { 1.0f,  1.5f,  0.1f,		1.0f, 0.0f}},

												 {{ 1.0f, -1.5f, 0.1f,		0.0f, 1.0f}, //1. quad
												 { 1.0f,  1.5f, 0.1f,		0.0f, 0.0f},
												 {-1.0f, -1.5f, 0.1f,		1.0f, 1.0f},
												 {-1.0f,  1.5f, 0.1f,		1.0f, 0.0f}},

												 {{-1.0f, -1.5f, 0.1f,		0.0f, 1.0f}, //1. quad
												 {-1.0f,  1.5f, 0.1f,		0.0f, 0.0f},
												 {-1.0f, -1.5f, -0.1f,		1.0f, 1.0f},
												 {-1.0f,  1.5f, -0.1f,		1.0f, 0.0f}},

												 {{-1.0f,  1.5f, -0.1f,		0.0f, 1.0f}, //1. quad
												 {-1.0f,  1.5f, 0.1f,		0.0f, 0.0f},
												 { 1.0f,  1.5f, -0.1f,		1.0f, 1.0f},
												 { 1.0f,  1.5f, 0.1f,		1.0f, 0.0f}},

												 {{-1.0f, -1.5f, 0.1f,		0.0f, 1.0f}, //1. quad
												 {-1.0f, -1.5f, -0.1f,		0.0f, 0.0f},
												 { 1.0f, -1.5f, 0.1f,		1.0f, 1.0f},
												 { 1.0f, -1.5f, -0.1f,		1.0f, 0.0f}}};
										 
	for (int j = 0; j < 6; ++j)
	{
		for(int i = 0; i < 4; ++i)
		{
			aSixQuadArray[j][i] = ArrayOfVertexArrays[j][i];
		}
	}
}


void FormeDoor::CreateVertexBuffers()
{
	for(int i = 0; i < 6; ++i)
	{
		D3D_Para->Direct3D_device->CreateVertexBuffer(sizeof(aSixQuadArray[i]), D3DUSAGE_WRITEONLY, CUSTOM_FVF_TEXMAPPING, 
														D3DPOOL_MANAGED, &SixQuadArray_buffer[i], NULL);
	}
}


void FormeDoor::FeedVertexBuffers()
{
	for(int i = 0; i < 6; ++i)
	{
		SixQuadArray_buffer[i]->Lock(0, sizeof(D3D_Para->pData), (void**)&D3D_Para->pData, 0);
		memcpy(D3D_Para->pData, aSixQuadArray[i], sizeof(aSixQuadArray[i]));
		SixQuadArray_buffer[i]->Unlock();
	}
}



void FormeDoor::SetTextureParameters()
{
	// change le type de Vertex
	D3D_Para->Direct3D_device->SetFVF(CUSTOM_FVF_TEXMAPPING);

	D3D_Para->Direct3D_device->SetTexture(0, pObjectTexture);
}


void FormeDoor::LoadTextureForObject()
{
	D3DXCreateTextureFromFile(D3D_Para->Direct3D_device,
                          "../Textures/tech_door_tex.png",
                          &pObjectTexture);
}


void FormeDoor::RenderingOfObject()
{
	for(int i = 0; i < 6; ++i)
	{
		D3D_Para->Direct3D_device->SetStreamSource(0, SixQuadArray_buffer[i], 0, sizeof(D3DVERTEX_TEX));
		D3D_Para->Direct3D_device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}