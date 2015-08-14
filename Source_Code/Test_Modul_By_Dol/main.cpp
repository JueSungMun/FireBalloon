#include "All_Header.h"

LPDIRECT3D9             g_pD3D       = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device

LPD3DXSPRITE g_pSprite;
WNDCLASSEX g_wc;
HWND g_hWnd;
LPDIRECT3DTEXTURE9 g_pTexture = NULL;
LPDIRECT3DTEXTURE9 g_pBullet = NULL;
LPDIRECT3DTEXTURE9 g_pBackground = NULL;
D3DXVECTOR3 vecPosition;
D3DXVECTOR3 vecPosBullet;
D3DXVECTOR3 vecPosBG;

time_t startTime, goaltime;

struct Image 
{
	BOOL Visible;
	LPDIRECT3DTEXTURE9 Texture;
	RECT Source;
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Center;
};

//Enemy enemyArray[5];
ObjectManager* om;
Image g_GoalLine;
TextDisplay score_display;
TextDisplay life_display;
int life = 200;
int currentScore =0;
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
	g_hWnd = CreateWindow( "D3D Tutorial", "FIREBALLOON",
		WS_OVERLAPPEDWINDOW, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, g_wc.hInstance, NULL );
}

void InitDX(void)
{
	InitD3D(g_hWnd);
	D3DXCreateSprite(g_pd3dDevice, &g_pSprite);

	vecPosition.x = SCREEN_WIDTH/2;
	vecPosition.y = SCREEN_HEIGHT/8;
	vecPosition.z = .0f;

	vecPosBG.x = .0f;
	vecPosBG.y = .0f;
	vecPosBG.z = .0f;

	// 적 이미지 초기화
	//RECT rct;
	//rct.left = 0; rct.top=0; rct.right=81; rct.bottom=56;
	ZeroMemory(&om, sizeof(ObjectManager));
//	for(int i=0; i<5; i++)
//		enemyArray[i].initEnemy(rct);
	

	// 골라인 초기화
	ZeroMemory(&g_GoalLine, sizeof(g_GoalLine));
	g_GoalLine.Source.left=0;
	g_GoalLine.Source.top=0;
	g_GoalLine.Source.right = 600;
	g_GoalLine.Source.bottom = 40;
	g_GoalLine.Visible = TRUE;
	g_GoalLine.Position.x = 0;
	g_GoalLine.Position.y = 700;

	time(&startTime);
	goaltime = startTime+50;

	score_display.initScore(g_hWnd);
	life_display.initLife(g_hWnd);
}

void LoadData(void)
{
	D3DXCreateTextureFromFileEx(g_pd3dDevice, IMG_FIREBALLOON,
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &g_pTexture);
	D3DXCreateTextureFromFileEx(g_pd3dDevice, IMG_BG,
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &g_pBackground); 
	D3DXCreateTextureFromFileEx( g_pd3dDevice, IMG_GOALLINE, 
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &g_GoalLine.Texture); 
	
	//for(int i=0; i<5; i++)
	//	enemyArray[i].setTexture(g_pd3dDevice, IMG_BIRD_RIGHT);
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
	RECT bgRect;
	D3DXVECTOR3 vecCenter;
	//D3DXVECTOR3 vecPosition;

	static int offset =0;

	rcSrcRect.left = 0;
	rcSrcRect.top = 0;
	rcSrcRect.right = 59;
	rcSrcRect.bottom = 88;

	vecCenter.x = .0f;
	vecCenter.y = .0f;
	vecCenter.z = .0f;

	srand((unsigned int)time(NULL));
	
	om = new ObjectManager;
	om->insertObj(0);
	om->insertObj(1);
	om->insertObj(2);
	RECT rct;
	rct.left = BIRD_RECT_LEFT; 
	rct.top = BIRD_RECT_TOP; 
	rct.right = BIRD_RECT_RIGHT; 
	rct.bottom = BIRD_RECT_BOTTOM;
	om->getEnemy(0).initEnemy(rct);
	om->getEnemy(1).initEnemy(rct);
	om->getEnemy(2).initEnemy(rct);
	om->getEnemy(0).manageMoving(g_pd3dDevice, 100);
	om->getEnemy(1).manageMoving(g_pd3dDevice, 200);
	om->getEnemy(2).manageMoving(g_pd3dDevice, 300);

	if (GetKeyState(VK_LEFT) & 0x80000000) 	vecPosition.x -= 7.0f;
	if (GetKeyState(VK_RIGHT) & 0x80000000) vecPosition.x += 7.0f;
	if (GetKeyState(VK_UP) & 0x80000000) vecPosition.y -= 5.0f;
	if (GetKeyState(VK_DOWN) & 0x80000000) 	vecPosition.y += 10.0f;

	// 충돌체크
	// 보이는 적중에 부딪히면 파괴
	
	for(int i=0; i<MAX_ENEMY; i++)
		if(om->getEnemy(i).getVisible())
		{
			RECT* source = om->getEnemy(i).getSource();
			D3DXVECTOR3* pos = om->getEnemy(i).getPosition();
			if(vecPosition.x < pos->x + source->right
				&&pos->x < vecPosition.x + rcSrcRect.right
				&&vecPosition.y < pos->y + source->bottom
				&&pos->y < vecPosition.y + rcSrcRect.bottom)
			{		
				om->getEnemy(i).setVisible(FALSE);
				currentScore += 100;
				life -= 10;
			}	
		}

	if(life<=0)
	{
		MessageBox(g_hWnd, "Oops!","You are dead!", MB_OK);
		exit(1);
	}
	//총알발사
	/*if (GetKeyState(0x5a) & 0x80000000) 
	{
		for (INT i=0; i<100; ++i)
		{
			if ( g_Bullet[i].Visible == FALSE )
			{
				g_Bullet[i].Visible = TRUE;
				g_Bullet[i].Position.x = vecPosition.x;
				g_Bullet[i].Position.y = vecPosition.y;
				break;
			}
		}
	}*/
	//총알속도
	/*for (INT i=0; i<100; ++i)
	{
		if ( g_Bullet[i].Visible == TRUE )	g_Bullet[i].Position.y -= 20.0f;

		if ( g_Bullet[i].Position.y < -40.0f )	g_Bullet[i].Visible = FALSE;	
	}*/

	//if ( vecPosBullet.y > -40.0f )
	//{
	//	vecPosBullet.y -= 5.0f;
	//}

	// Clear the backbuffer to a blue color
	//g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100,100,255), 1.0f, 0 );

	// Begin the scene
	if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
	{
		g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		//g_pSprite->Draw(g_pBullet, &rcSrcBullet, &vecCenter, &vecPosBullet, 0xffffffff);

		//배경그리기
		//top sprite
		bgRect.left = 0;
		bgRect.right = 600;
		bgRect.top = 0;
		bgRect.bottom = SCREEN_HEIGHT;
		vecPosBG.y = -(float)offset;
		g_pSprite->Draw(g_pBackground, &bgRect, NULL, &vecPosBG, 0xFFFFFFFF);

		bgRect.top = 0;
		bgRect.bottom = offset;
		
		D3DXVECTOR3 vecPosBG2(0,(float)(SCREEN_HEIGHT-offset),0);
		g_pSprite->Draw(g_pBackground, &bgRect, NULL, &vecPosBG2, 0xFFFFFFFF);
		offset++;
		offset = offset%SCREEN_HEIGHT;

		/*
		bgRect.left=0;
		bgRect.right=600;

		bgRect.top=900-offset;
		bgRect.bottom=900;
		g_pSprite->Draw(g_pBackground, &bgRect, NULL, &vecPosBG, 0xFFFFFFFF);

		//bottom sprite
		bgRect.top=0;
		bgRect.bottom=SCREEN_HEIGHT-offset;
		D3DXVECTOR3 vecPosBG2(0,(float)offset,0);
		g_pSprite->Draw(g_pBackground, &bgRect, NULL, &vecPosBG2, 0xFFFFFFFF);
		offset=offset%600;
		*/
		
		//시작하고 10초뒤에 골라인 올라옴
		time_t crtTime;
		time(&crtTime);
		if(goaltime < crtTime)
		{
			g_GoalLine.Position.y -= 3.0f;
			g_pSprite->Draw( g_GoalLine.Texture, &g_GoalLine.Source, &g_GoalLine.Center, &g_GoalLine.Position, 0xffffffff );
		}
		
		for(int i=0; i<MAX_ENEMY; i++)
		{
			if(om->getEnemy(i).getVisible() == TRUE)
				g_pSprite->Draw( om->getEnemy(i).getTexture(), om->getEnemy(i).getSource(), om->getEnemy(i).getCenter(), om->getEnemy(i).getPosition(), 0xffffffff );
		}
		// 골라인과 플레이어가 만나면 
		if ( g_GoalLine.Position.y < vecPosition.y )
		{
			// 스테이지 클리어
			MessageBox(NULL, "STAGE CLEAR!", "Congraturations!", MB_OK);
			exit(0);
		}
		//총알그려줌
		/*for ( INT i=0; i<100; ++i )
		{
			if ( g_Bullet[i].Visible == TRUE )
			{
				g_pSprite->Draw(g_Bullet[i].Texture, &g_Bullet[i].Source, &g_Bullet[i].Center, &g_Bullet[i].Position, 0xffffffff);
			}
		}*/

		g_pSprite->Draw(g_pTexture, &rcSrcRect, &vecCenter, &vecPosition, 0xffffffff);
		//g_pSprite->End();
		
	//	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	//	D3DXCreateTextureFromFileInMemory(g_pd3dDevice,(LPCVOID)life,100,&g_pBackground);
		score_display.showScore(std::to_string((crtTime-startTime)*10+currentScore));
		life_display.showLife(std::to_string(life));
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




