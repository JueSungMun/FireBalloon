#include "Graphic_Lib.h"

Graphic_Lib::Graphic_Lib() :  g_pD3D(NULL), g_pd3dDevice(NULL)
{
}

Graphic_Lib::~Graphic_Lib()
{
    if( g_pD3D != NULL )       
        g_pD3D->Release();

	if( g_pd3dDevice != NULL ) 
        g_pd3dDevice->Release();
}

HRESULT Graphic_Lib::InitD3D( HWND hWnd )
{
	g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.hDeviceWindow = hWnd;

	g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice );

    return S_OK;
}

bool Graphic_Lib::Initilize( HWND hWnd )
{
	//SUCCEEDED
	if(!SUCCEEDED(InitD3D(hWnd)))
	{
		MessageBox(NULL, _T("DirectX Initialize Error"), NULL, NULL);
		return false;
	}
	return true;
}

void Graphic_Lib::Clear(D3DCOLOR color)
{
	g_pd3dDevice->Clear(0,NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
}

void Graphic_Lib::Begin()
{
	g_pd3dDevice->BeginScene();
}

void Graphic_Lib::End()
{
	g_pd3dDevice->EndScene();
}

void Graphic_Lib::Present()
{
	g_pd3dDevice->Present(NULL,NULL,NULL,NULL);
}