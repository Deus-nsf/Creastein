#pragma once

#include "header_ressources.hpp"
#include "cl_Direct3D_Parameters.hpp"
#include "cl_CustomForme.hpp"


class FormePyramide :  public CustomForme
{
protected:
	//liste des vertex arrays constituant ma forme
	D3DVERTEX aPyramideCone[12];
	D3DVERTEX aQuad[4];

	//liste des vertex buffers constituant ma forme
	LPDIRECT3DVERTEXBUFFER9	 PyramideCone_buffer;
	LPDIRECT3DVERTEXBUFFER9	 Quad_buffer;

public:
	FormePyramide();
	~FormePyramide();

	virtual void SetForms();
	virtual void CreateVertexBuffers();
	virtual void FeedVertexBuffers();
	virtual void LoadTextureForObject();
	virtual void SetTextureParameters();

	virtual void RenderingOfObject();
};