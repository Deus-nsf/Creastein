
#include "cl_FormeCube.hpp"


FormeCube::FormeCube() : CustomForme()
{
	for(int i = 0; i < 2; ++i)
		SixQuadArray_buffer[i] = NULL;
}


FormeCube::~FormeCube()
{

}


// creation d'un cube de 2/2/2 metres
void FormeCube::SetForms()
{
	// arranged as triangle strips
	D3DVERTEX_TEX ArrayOfVertexArrays[6][4] = {{{ -1.0f, -1.0f, -1.0f,		0.0f, 0.0f}, //1. quad
												 {-1.0f,  1.0f, -1.0f,		0.0f, 1.0f},
												 { 1.0f, -1.0f, -1.0f,		1.0f, 0.0f},
												 { 1.0f,  1.0f, -1.0f,		1.0f, 1.0f}},

												 {{ 1.0f, -1.0f, -1.0f,		0.0f, 0.0f}, //1. quad
												 { 1.0f,  1.0f, -1.0f,		0.0f, 1.0f},
												 { 1.0f, -1.0f,  1.0f,		1.0f, 0.0f},
												 { 1.0f,  1.0f,  1.0f,		1.0f, 1.0f}},

												 {{ 1.0f, -1.0f, 1.0f,		0.0f, 0.0f}, //1. quad
												 { 1.0f,  1.0f, 1.0f,		0.0f, 1.0f},
												 {-1.0f, -1.0f, 1.0f,		1.0f, 0.0f},
												 {-1.0f,  1.0f, 1.0f,		1.0f, 1.0f}},

												 {{-1.0f, -1.0f, 1.0f,		0.0f, 0.0f}, //1. quad
												 {-1.0f,  1.0f, 1.0f,		0.0f, 1.0f},
												 { -1.0f, -1.0f, -1.0f,		1.0f, 0.0f},
												 {-1.0f,  1.0f, -1.0f,		1.0f, 1.0f}},

												 {{-1.0f,  1.0f, -1.0f,		0.0f, 0.0f}, //1. quad
												 {-1.0f,  1.0f, 1.0f,		0.0f, 1.0f},
												 { 1.0f,  1.0f, -1.0f,		1.0f, 0.0f},
												 { 1.0f,  1.0f, 1.0f,		1.0f, 1.0f}},

												 {{-1.0f, -1.0f, 1.0f,		0.0f, 0.0f}, //1. quad
												 {-1.0f, -1.0f, -1.0f,		0.0f, 1.0f},
												 { 1.0f, -1.0f, 1.0f,		1.0f, 0.0f},
												 { 1.0f, -1.0f, -1.0f,		1.0f, 1.0f}}};
										 
	for (int j = 0; j < 6; ++j)
	{
		for(int i = 0; i < 4; ++i)
		{
			aSixQuadArray[j][i] = ArrayOfVertexArrays[j][i];
		}
	}
}


void FormeCube::CreateVertexBuffers()
{
	for(int i = 0; i < 6; ++i)
	{
		D3D_Para->Direct3D_device->CreateVertexBuffer(sizeof(aSixQuadArray[i]), D3DUSAGE_WRITEONLY, CUSTOM_FVF_TEXMAPPING, 
														D3DPOOL_MANAGED, &SixQuadArray_buffer[i], NULL);
	}
}


void FormeCube::FeedVertexBuffers()
{
	for(int i = 0; i < 6; ++i)
	{
		SixQuadArray_buffer[i]->Lock(0, sizeof(D3D_Para->pData), (void**)&D3D_Para->pData, 0);
		memcpy(D3D_Para->pData, aSixQuadArray[i], sizeof(aSixQuadArray[i]));
		SixQuadArray_buffer[i]->Unlock();
	}
}



void FormeCube::SetTextureParameters()
{
	// change le type de Vertex
	D3D_Para->Direct3D_device->SetFVF(CUSTOM_FVF_TEXMAPPING);

	D3D_Para->Direct3D_device->SetTexture(0, pObjectTexture);
}


void FormeCube::LoadTextureForObject()
{
	D3DXCreateTextureFromFile(D3D_Para->Direct3D_device,
                          "../Textures/wall_tex.png",
                          &pObjectTexture);
}


void FormeCube::RenderingOfObject()
{
	for(int i = 0; i < 6; ++i)
	{
		D3D_Para->Direct3D_device->SetStreamSource(0, SixQuadArray_buffer[i], 0, sizeof(D3DVERTEX_TEX));
		D3D_Para->Direct3D_device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}