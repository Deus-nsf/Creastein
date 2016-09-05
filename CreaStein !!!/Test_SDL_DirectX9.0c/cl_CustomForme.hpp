#pragma once

#include "header_ressources.hpp"
#include "cl_Direct3D_Parameters.hpp"


class CustomForme
{
protected:
	Direct3D_Parameters* D3D_Para;

	// texture for object
	LPDIRECT3DTEXTURE9 pObjectTexture;

public:
	CustomForme();
	~CustomForme();

	virtual void CreateRessourcesForObject();
	virtual void SetForms() = 0;
	virtual void CreateVertexBuffers() = 0;
	virtual void FeedVertexBuffers() = 0;
	virtual void LoadTextureForObject();
	virtual void SetTextureParameters() = 0;

	virtual void RenderingOfObject() = 0;
};