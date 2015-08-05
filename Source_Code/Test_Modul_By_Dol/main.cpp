#include <d3d9.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 ) 
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define IMG_FIREBALLOON "..\\Resource\\bird\\bird1.jpeg"
#define IMG_BIRD "..\\Resource\\bird\\bird2.jpeg"
#define IMG_ITEM "..\\Resource\\bird\\bird3.jpeg"

LPDIRECT3D9             g_pD3D       = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device

LPD3DXSPRITE g_pSprite;
WNDCLASSEX g_wc;
HWND g_hWnd;
LPDIRECT3DTEXTURE9 g_pTexture = NULL;
LPDIRECT3DTEXTURE9 g_pBullet = NULL;
D3DXVECTOR3 vecPosition;
D3DXVECTOR3 vecPosBullet;

struct Image 
{
	BOOL Visible;
	LPDIRECT3DTEXTURE9 Texture;
	RECT Source;
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Center;
};

Image g_Bullet[100];
Image g_Enemy;
INT g_EnemyGage = 200;

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
HRESULT InitD3D( HWND hWnd );

void InitWin(void)
{
	// Register the window class
	WNDCLASSEX g_wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"D3D Tutorial", NULL };
	RegisterClassEx( &g_wc );

	// Create the application's window
	g_hWnd = CreateWindow( "D3D Tutorial", "Fireballoon",
		WS_OVERLAPPEDWINDOW, 100, 100, 600, 600,
		NULL, NULL, g_wc.hInstance, NULL );
}

void InitDX(void)
{
	InitD3D(g_hWnd);
	D3DXCreateSprite(g_pd3dDevice, &g_pSprite);

	vecPosition.x = 300.0f;
	vecPosition.y = 450.0f;
	vecPosition.z = .0f;

	vecPosBullet.x = -30.0f;
	vecPosBullet.y = .0f;
	vecPosBullet.z = .0f;

	ZeroMemory(&g_Bullet, sizeof(g_Bullet));
	g_Bullet[0].Source.left = 0;
	g_Bullet[0].Source.top = 0;
	g_Bullet[0].Source.right = 427;
	g_Bullet[0].Source.bottom = 285;

	// 적 이미지 초기화
	ZeroMemory(&g_Enemy, sizeof(g_Enemy));
	g_Enemy.Source.left = 0;
	g_Enemy.Source.top = 0;
	g_Enemy.Source.right = 427;
	g_Enemy.Source.bottom = 285;
	g_Enemy.Visible = TRUE;

	g_Enemy.Position.x = 150.0f;
	g_Enemy.Position.y = 10.0f;
}

void LoadData(void)
{
	D3DXCreateTextureFromFile(g_pd3dDevice, IMG_FIREBALLOON, &g_pTexture);
	D3DXCreateTextureFromFile(g_pd3dDevice, IMG_ITEM, &g_Bullet[0].Texture);
	
	for (INT i=1; i<100; ++i)
	{
		g_Bullet[i].Texture = g_Bullet[0].Texture;
		g_Bullet[i].Source = g_Bullet[0].Source;
	}


	D3DXCreateTextureFromFileEx( g_pd3dDevice, IMG_BIRD, 
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &g_Enemy.Texture); 
}

void Initilize(void)
{
	InitWin();
	InitDX();
	LoadData();

	// Show the window
	ShowWindow( g_hWnd, SW_SHOWDEFAULT );
	UpdateWindow( g_hWnd );
}

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
{
	g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,	D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice );

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
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
VOID Render()
{
	RECT rcSrcRect;
	D3DXVECTOR3 vecCenter;
	//D3DXVECTOR3 vecPosition;

	rcSrcRect.left = 0;
	rcSrcRect.top = 0;
	rcSrcRect.right = 120;
	rcSrcRect.bottom = 95;

	vecCenter.x = .0f;
	vecCenter.y = .0f;
	vecCenter.z = .0f;

	//RECT rcSrcBullet;
	//rcSrcBullet.left = 0;
	//rcSrcBullet.top = 0;
	//rcSrcBullet.right = 13;
	//rcSrcBullet.bottom = 26;

	//vecPosition.x = 10.0f;
	//vecPosition.y = 10.0f;
	//vecPosition.z = .0f;

	if (GetKeyState(VK_LEFT) & 0x80000000) 	vecPosition.x -= 10.0f;

	if (GetKeyState(VK_RIGHT) & 0x80000000) vecPosition.x += 10.0f;
	
	if (GetKeyState(VK_UP) & 0x80000000) vecPosition.y -= 10.0f;

	if (GetKeyState(VK_DOWN) & 0x80000000) 	vecPosition.y += 10.0f;
	
	// 충돌체크
	for (INT i=0; i<100; ++i)
	{
		// 보이는 총알 중에
		if ( g_Bullet[i].Visible == TRUE )
		{

			// 충돌 되었으면
			if ( g_Bullet[i].Position.x < g_Enemy.Position.x + g_Enemy.Source.right
				&&g_Enemy.Position.x < g_Bullet[i].Position.x + g_Bullet[i].Source.right
				&&g_Bullet[i].Position.y < g_Enemy.Position.y + g_Enemy.Source.bottom
				&&g_Enemy.Position.y < g_Bullet[i].Position.y + g_Bullet[i].Source.bottom
				)
			{
				// 충돌한 총알은 안보이고, 게이지 깍기
				if ( g_EnemyGage >= 0 )
				{
					g_Bullet[i].Visible = FALSE;
					g_EnemyGage--;
				}
			}
		}
	}

	// 적의 게이지가 0보다 작으면 안보이기
	if ( g_EnemyGage <= 0 )	g_Enemy.Visible = FALSE;

	if (GetKeyState(0x5a) & 0x80000000) 
	{
		for (INT i=0; i<100; ++i)
		{
			if ( g_Bullet[i].Visible == FALSE )
			{
				g_Bullet[i].Visible = TRUE;
				g_Bullet[i].Position.x = vecPosition.x + 60.0f - 6.0f;
				g_Bullet[i].Position.y = vecPosition.y;
				break;
			}
		}
	}

	for (INT i=0; i<100; ++i)
	{
		if ( g_Bullet[i].Visible == TRUE )	g_Bullet[i].Position.y -= 5.0f;

		if ( g_Bullet[i].Position.y < -40.0f )	g_Bullet[i].Visible = FALSE;
	}

	//if ( vecPosBullet.y > -40.0f )
	//{
	//	vecPosBullet.y -= 5.0f;
	//}

	// Clear the backbuffer to a blue color
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100,100,255), 1.0f, 0 );

	// Begin the scene
	if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
	{
		g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		//g_pSprite->Draw(g_pBullet, &rcSrcBullet, &vecCenter, &vecPosBullet, 0xffffffff);

		if ( g_Enemy.Visible == TRUE )
			g_pSprite->Draw( g_Enemy.Texture, &g_Enemy.Source, &g_Enemy.Center, &g_Enemy.Position, 0xffffffff );

		for ( INT i=0; i<100; ++i )
		{
			if ( g_Bullet[i].Visible == TRUE )
			{
				g_pSprite->Draw(g_Bullet[i].Texture, &g_Bullet[i].Source, &g_Bullet[i].Center, &g_Bullet[i].Position, 0xffffffff);
			}
		}

		g_pSprite->Draw(g_pTexture, &rcSrcRect, &vecCenter, &vecPosition, 0xffffffff);
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
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
    case WM_DESTROY:
        Cleanup();
        PostQuitMessage( 0 );
        return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	Initilize();

	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );
	while( msg.message!=WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
			Render();
	}

    UnregisterClass( "D3D Tutorial", g_wc.hInstance );
    return 0;
}




