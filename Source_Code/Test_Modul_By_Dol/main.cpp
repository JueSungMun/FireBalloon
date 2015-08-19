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

time_t startTime, goaltime, currentTime;

struct Image 
{
	BOOL Visible;
	LPDIRECT3DTEXTURE9 Texture;
	RECT Source;
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Center;
};

ObjectManager* om;
Image g_GoalLine;
TextDisplay score_display;
TextDisplay life_display;
int life = 200;
int currentScore =0;
int currentEnemyNum=0;
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
HRESULT InitD3D( HWND hWnd );
LPD3DXFONT scoreFont;
LPD3DXFONT lifeFont;

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

	// �� �̹��� �ʱ�ȭ
	ZeroMemory(&om, sizeof(ObjectManager));
	om = new ObjectManager;
	
	// ����� �ʱ�ȭ
	ZeroMemory(&g_GoalLine, sizeof(g_GoalLine));
	g_GoalLine.Source.left = 0;
	g_GoalLine.Source.top = 0;
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
	D3DXCreateFont(g_pd3dDevice, 30,15, 255, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "����ü", &scoreFont);
	D3DXCreateFont(g_pd3dDevice, 30,15, 255, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "����ü", &lifeFont);
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
	if( om != NULL )
		delete om;
}

VOID GeneratingEnemy()
{
	om->insertObj();
	currentEnemyNum++;
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

	static int offset =0;

	rcSrcRect.left = 0;
	rcSrcRect.top = 0;
	rcSrcRect.right = 59;
	rcSrcRect.bottom = 88;

	vecCenter.x = .0f;
	vecCenter.y = .0f;
	vecCenter.z = .0f;

	srand((unsigned int)time(NULL));
	
	if(currentEnemyNum < MAX_ENEMY )
	{
		if(GetTickCount() %60==0)
			GeneratingEnemy();
	}

	if (GetKeyState(VK_LEFT) & 0x80000000) 	vecPosition.x -= 7.0f;
	if (GetKeyState(VK_RIGHT) & 0x80000000) vecPosition.x += 7.0f;
	if (GetKeyState(VK_UP) & 0x80000000) vecPosition.y -= 5.0f;
	if (GetKeyState(VK_DOWN) & 0x80000000) 	vecPosition.y += 10.0f;

	if(currentEnemyNum>0)
	{	
		int tmp = currentEnemyNum;
		for(int i=0; i<tmp; i++)
			if(om->getAlive(i))
			{
				if( !(om->getEnemy(i).manageMoving(g_pd3dDevice, i*100+300)) ) 
				{
					//���� ��ġ�� ���Ʒ��� ����� �ı�
					om->deleteObj(i);
					currentEnemyNum--;
				} 
				else 
				{
					// �浹üũ
					// ���̴� ���߿� �ε����� �ı�		
					D3DXVECTOR3* pos = om->getEnemy(i).getPosition();
					if( vecPosition.x < pos->x + BIRD_RECT_RIGHT
						&&pos->x < vecPosition.x + rcSrcRect.right
						&&vecPosition.y < pos->y + BIRD_RECT_BOTTOM
						&&pos->y < vecPosition.y + rcSrcRect.bottom)
					{		
						currentScore -= 50;
						life -= 10;
						currentEnemyNum--;
						om->deleteObj(i);
					}	
				}
			}
	}

	if(life<=0)
	{
		MessageBox(g_hWnd, "Oops!","You are dead!", MB_OK);
		exit(1);
	}
	//�Ѿ˹߻�
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
	//�Ѿ˼ӵ�
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

		//���׸���
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
				
		//�����ϰ� 10�ʵڿ� ����� �ö��
		time_t crtTime;
		time(&crtTime);
		if(goaltime < crtTime)
		{
			g_GoalLine.Position.y -= 3.0f;
			g_pSprite->Draw( g_GoalLine.Texture, &g_GoalLine.Source, &g_GoalLine.Center, &g_GoalLine.Position, 0xffffffff );
		}
		
		//�� �׸�
		if(currentEnemyNum > 0)
		for(int i=0; i<MAX_ENEMY; i++)
		{
			if(om->getAlive(i) == TRUE)
				g_pSprite->Draw( om->getEnemy(i).getTexture(), om->getEnemy(i).getSource(), om->getEnemy(i).getCenter(), om->getEnemy(i).getPosition(), 0xffffffff );
		}

		// ����ΰ� �÷��̾ ������ 
		if ( g_GoalLine.Position.y < vecPosition.y )
		{
			// �������� Ŭ����
			MessageBox(NULL, "STAGE CLEAR!", "Congraturations!", MB_OK);
			exit(0);
		}
		//�Ѿ˱׷���
		/*for ( INT i=0; i<100; ++i )
		{
			if ( g_Bullet[i].Visible == TRUE )
			{
				g_pSprite->Draw(g_Bullet[i].Texture, &g_Bullet[i].Source, &g_Bullet[i].Center, &g_Bullet[i].Position, 0xffffffff);
			}
		}*/

		g_pSprite->Draw(g_pTexture, &rcSrcRect, &vecCenter, &vecPosition, 0xffffffff);
		
		RECT scoreRect = {400,20,-1,-1};
		RECT lifeRect = {20,20,-1,-1};

		std::string scoreStr = "SCORE ";
		scoreStr.append(std::to_string((crtTime-startTime)*10+currentScore));

		std::string lifeStr = "LIFE ";
		lifeStr.append(std::to_string(life));

		if(scoreFont)
			scoreFont->DrawText(g_pSprite, scoreStr.c_str(), scoreStr.length(), &scoreRect, DT_NOCLIP, D3DXCOLOR(0,0,0,1));

		if(lifeFont)
			lifeFont->DrawText(g_pSprite, lifeStr.c_str(), lifeStr.length(), &lifeRect,DT_NOCLIP, D3DXCOLOR(0,0,0,1));
	
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




