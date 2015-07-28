#include "DirectX_Lib.h"

DirectX_Lib::DirectX_Lib() :  g_pD3D(NULL), g_pd3dDevice(NULL), backGroundTexture(NULL)
{
}

DirectX_Lib::DirectX_Lib(LPCWSTR windowName, int posX, int posY, int width, int height) :  g_pD3D(NULL), g_pd3dDevice(NULL), backGroundTexture(NULL)
{
	InitWin(windowName, posX, posY, width, height);
	InitDX();
}

DirectX_Lib::~DirectX_Lib()
{
	Cleanup();
}

void DirectX_Lib::InitWin(void)
{
	// Register the window class
	WNDCLASSEX g_wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		_T("D3D Tutorial"), NULL };
	RegisterClassEx( &g_wc );

	// Create the application's window
	g_hWnd = CreateWindow( _T("D3D Tutorial"), _T("D3D Tutorial 02: Vertices"),
		WS_OVERLAPPEDWINDOW, 100, 100, 600, 600,
		NULL, NULL, g_wc.hInstance, NULL );
}

void DirectX_Lib::InitWin(LPCWSTR windowName, int posX, int posY, int width, int height)
{
	// Register the window class
	WNDCLASSEX g_wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		_T("D3D Tutorial"), NULL };
	RegisterClassEx( &g_wc );

	// Create the application's window
	g_hWnd = CreateWindow( _T("D3D Tutorial"), windowName,
		WS_OVERLAPPEDWINDOW, posX, posY, width, height,
		NULL, NULL, g_wc.hInstance, NULL );
}

void DirectX_Lib::InitDX(void)
{
	InitD3D(g_hWnd);
	D3DXCreateSprite(g_pd3dDevice, &g_pSprite);
}

HRESULT DirectX_Lib::InitD3D( HWND hWnd )
{
	g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );


    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;


	g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice );

    return S_OK;
}

void DirectX_Lib::LoadBackGroundData(void)
{
	D3DXCreateTextureFromFile(g_pd3dDevice, _T(BACKGROUND_TEXTURE_PATH), &backGroundTexture);
}

void DirectX_Lib::Initilize(void)
{
	InitWin();
	InitDX();
	LoadBackGroundData();

	// Show the window
	ShowWindow( g_hWnd, SW_SHOWDEFAULT );
	UpdateWindow( g_hWnd );
}

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID DirectX_Lib::Cleanup()
{
	if ( g_pSprite != NULL)
		g_pSprite->Release();

    if( g_pd3dDevice != NULL ) 
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )       
        g_pD3D->Release();
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID DirectX_Lib::Render()
{
	RECT rcSrcRect;
	D3DXVECTOR3 vecCenter;
	D3DXVECTOR3 vecPosition;

	rcSrcRect.left = 0;
	rcSrcRect.top = 0;
	rcSrcRect.right = 600;
	rcSrcRect.bottom = 600;

	vecCenter.x = .0f;
	vecCenter.y = .0f;
	vecCenter.z = .0f;

	vecPosition.x = 0.0f;
	vecPosition.y = 0.0f;
	vecPosition.z = .0f;


    // Clear the backbuffer to a blue color
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
		g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		g_pSprite->Draw(backGroundTexture, &rcSrcRect, &vecCenter, &vecPosition, 0xffffffff);
		g_pSprite->End();

        // End the scene
        g_pd3dDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI DirectX_Lib::MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            //Cleanup();
            PostQuitMessage( 0 );
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}

WNDCLASSEX DirectX_Lib::GetValueGWC()
{
	return g_wc;
};