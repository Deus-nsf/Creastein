
#include "cl_FormePyramide.hpp"


FormePyramide::FormePyramide() : CustomForme()
{
	PyramideCone_buffer = NULL;
	Quad_buffer = NULL;
}


FormePyramide::~FormePyramide()
{

}



void FormePyramide::SetForms()
{
	// arranged as triangle lists
	D3DVERTEX VertexArray[12] = {{ 0.0f, 0.5f, 0.0f,0xffff0000}, //1. tri (NEW)
                         {-0.5f,-0.5f,-0.5f,0xff00ff00},
                         { 0.5f,-0.5f,-0.5f,0xff0000ff},
                         { 0.0f, 0.5f, 0.0f,0xffff0000}, //2. tri (NEW)
                         {-0.5f,-0.5f, 0.5f,0xff0000ff},
                         {-0.5f,-0.5f,-0.5f,0xff00ff00},
                         { 0.0f, 0.5f, 0.0f,0xffff0000}, //3. tri (NEW)
                         { 0.5f,-0.5f, 0.5f,0xff00ff00},
                         {-0.5f,-0.5f, 0.5f,0xff0000ff},
                         { 0.0f, 0.5f, 0.0f,0xffff0000}, //4. tri (NEW)
                         { 0.5f,-0.5f,-0.5f,0xff0000ff},
                         { 0.5f,-0.5f, 0.5f,0xff00ff00}};

	// arranged as triangle strips
	D3DVERTEX VertexArray_2[4] = {{-0.5f,-0.5f,-0.5f,0xff00ff00},     //1 quad (NEW)
                     { 0.5f,-0.5f,-0.5f,0xff0000ff},
                     {-0.5f,-0.5f, 0.5f,0xff0000ff},
                     { 0.5f,-0.5f, 0.5f,0xff00ff00}};


	for (int i = 0; i < 12; ++i)
	{
		aPyramideCone[i] = VertexArray[i];
	}

	for (int i = 0; i < 4; ++i)
	{
		aQuad[i] = VertexArray_2[i];
	}
}


void FormePyramide::CreateVertexBuffers()
{
	D3D_Para->Direct3D_device->CreateVertexBuffer(sizeof(aPyramideCone), D3DUSAGE_WRITEONLY, CUSTOM_FVF, 
                                    D3DPOOL_MANAGED, &PyramideCone_buffer, NULL);

	D3D_Para->Direct3D_device->CreateVertexBuffer(sizeof(aQuad), D3DUSAGE_WRITEONLY, CUSTOM_FVF,
                                    D3DPOOL_MANAGED, &Quad_buffer, NULL);
}


void FormePyramide::FeedVertexBuffers()
{
	PyramideCone_buffer->Lock(0, sizeof(D3D_Para->pData), (void**)&D3D_Para->pData, 0);
	memcpy(D3D_Para->pData, aPyramideCone, sizeof(aPyramideCone));
	PyramideCone_buffer->Unlock();

	Quad_buffer->Lock(0, sizeof(D3D_Para->pData), (void**)&D3D_Para->pData, 0);
	memcpy(D3D_Para->pData, aQuad, sizeof(aQuad));
	Quad_buffer->Unlock();
}



void FormePyramide::SetTextureParameters()
{
	D3D_Para->Direct3D_device->SetTexture(0, NULL);
}


void FormePyramide::LoadTextureForObject()
{
	/*D3DXCreateTextureFromFile(D3D_Para->Direct3D_device,
                          "../Textures/wall_tex.png",
                          &pObjectTexture);*/
}


void FormePyramide::RenderingOfObject()
{
	D3D_Para->Direct3D_device->SetStreamSource(0, PyramideCone_buffer, 0, sizeof(D3DVERTEX));
	D3D_Para->Direct3D_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 4);

	D3D_Para->Direct3D_device->SetStreamSource(0, Quad_buffer, 0, sizeof(D3DVERTEX));
	D3D_Para->Direct3D_device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}