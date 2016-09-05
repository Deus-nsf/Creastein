#pragma once

#include "header_ressources.hpp"
#include "cl_Direct3D_Parameters.hpp"
#include "cl_CustomForme.hpp"


class FormeSolPierre :  public CustomForme
{
protected:
	//liste des vertex arrays constituant ma forme
	D3DVERTEX_TEX aPlane[4];

	//liste des vertex bufers constituant ma forme
	LPDIRECT3DVERTEXBUFFER9	 Plane_buffer;

public:
	FormeSolPierre();
	~FormeSolPierre();

	virtual void SetForms();
	virtual void CreateVertexBuffers();
	virtual void FeedVertexBuffers();
	virtual void LoadTextureForObject();
	virtual void SetTextureParameters();

	virtual void RenderingOfObject();
};