
#include "cl_CustomForme.hpp"


CustomForme::CustomForme()
{
	D3D_Para = Direct3D_Parameters::GetSingleton();
}


CustomForme::~CustomForme()
{
	D3D_Para = Direct3D_Parameters::GetSingleton();
}


void CustomForme::CreateRessourcesForObject()
{
	SetForms();
	CreateVertexBuffers();
	FeedVertexBuffers();
	LoadTextureForObject();
}


void CustomForme::LoadTextureForObject()
{
	pObjectTexture = NULL;
}