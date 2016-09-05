
#include "cl_Direct3D_Parameters.hpp"


Direct3D_Parameters::Direct3D_Parameters()
{
	// permet d'obtenir la res du bureau
	GetWindowRect(GetDesktopWindow(), &Screen);
}


Direct3D_Parameters* Direct3D_Parameters::GetSingleton()
{
	static Direct3D_Parameters oDirect3D_Parameters;
	return &oDirect3D_Parameters;
}


Direct3D_Parameters::~Direct3D_Parameters()
{

}


void Direct3D_Parameters::InitD3D()
{
	CreateD3D_Object();
	SetDeviceParameters();
	CreateD3D_Device();
	SetStates();
}


void Direct3D_Parameters::CreateD3D_Object()
{
	Direct3D_object = Direct3DCreate9(D3D_SDK_VERSION);
	if( Direct3D_object == NULL )
	{
		MessageBox(GetActiveWindow(), "Could not create Direct3D Object", "D3D_OBJ ERR", MB_OK);
	}
}


void Direct3D_Parameters::SetDeviceParameters()
{
	ZeroMemory(&present_parameters, sizeof(present_parameters));

	present_parameters.Windowed = false;
	present_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	present_parameters.EnableAutoDepthStencil = true;
	present_parameters.AutoDepthStencilFormat = D3DFMT_D16;
	present_parameters.hDeviceWindow = GetActiveWindow();	// c'est ici qu'on recupere la fenêtre SDL pour qu'elle devienne la Device Window
	present_parameters.BackBufferWidth = Screen.right;
	present_parameters.BackBufferHeight = Screen.bottom;
	present_parameters.BackBufferFormat = D3DFMT_X8R8G8B8;	// Back Buffer HQ
	present_parameters.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;	// MSAAx8 activé
}


void Direct3D_Parameters::CreateD3D_Device()
{
	if( FAILED(Direct3D_object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
           /*c'est ici qu'on recupe la fenêtre SDL pour qu'elle devienne la Render Window*/ GetActiveWindow(),
		   D3DCREATE_SOFTWARE_VERTEXPROCESSING, &present_parameters, &Direct3D_device)))
	{
	   MessageBox(GetActiveWindow(), "Could not create Direct3D Device", "D3D_DEV ERR", MB_OK);
	}
}


void Direct3D_Parameters::SetStates()
{
	// set Flexible Vertex Format
	Direct3D_device->SetFVF(CUSTOM_FVF);
	
    D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(0.0f, 0.0f, 0.0f),	//Camera Position
                                 &D3DXVECTOR3(0.0f, 0.0f, 1.0f),		//Look At Position
                                 &D3DXVECTOR3(0.0f, 1.0f, 0.0f));		//Up Direction
    Direct3D_device->SetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixPerspectiveFovLH(&projection_matrix, /*fov in radiants*/ D3DX_PI / 4.0f,
		/*aspect ratio*/(float)Screen.right/Screen.bottom, /*near plane ("meters")*/ 0.2f, /*far plane*/ 1000.0f);

	// set transform
	Direct3D_device->SetTransform(D3DTS_PROJECTION, &projection_matrix);

	// setting render states //
	Direct3D_device->SetRenderState(D3DRS_AMBIENT, RGB(255,255,255));
	Direct3D_device->SetRenderState(D3DRS_LIGHTING, false);
	Direct3D_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Direct3D_device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

	// ANISOTROPIC FILTERING x16 DE PARTOUUUUT !!! et textrure en mode WRAP par defaut
	for(unsigned i = 0; i < 8; ++i)
	 {
		 Direct3D_device->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
		 Direct3D_device->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
		 Direct3D_device->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
		 Direct3D_device->SetSamplerState(i, D3DSAMP_MAXANISOTROPY, 16);
		 Direct3D_device->SetSamplerState(i, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		 Direct3D_device->SetSamplerState(i, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	 }
	// end of setting //
}