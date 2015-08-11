#include "GameScene.h"

GameScene::GameScene() : spriter(NULL), texture(NULL)
{ 
	position.x=0;
	position.y=0;
	position.z=0;

	color = D3DCOLOR_ARGB(255,255,255,255);
	background = _T("..\\Resource\\bird_test\\background.png");
	SetSceneNumber(3);
}

GameScene::~GameScene()
{
	if(spriter != NULL)
	{
		spriter->Release();
		spriter=0;
	}
	if(texture != NULL)
	{
		texture->Release();
		texture = 0;
	}
}

void GameScene::Initialize(HWND& hWnd)
{
	if(!Manage_Scene::Initialized())
	{
		Manage_Scene::Initialize(hWnd);
	}
	
	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(gDevice->g_pd3dDevice, background, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &texture)))
	{
		MessageBox(NULL,_T("Image Load error"),NULL,NULL);
	}
	
	if (!SUCCEEDED(D3DXCreateSprite(gDevice->g_pd3dDevice, &spriter)))
	{
		MessageBox(NULL,_T("Error on generating spriter"),NULL,NULL);
	}
}


void GameScene::Draw(float gameTime)
{
	static int offset = 1;
	gDevice->Clear(D3DCOLOR_XRGB(0,0,255));
	gDevice->Begin();

	RECT bgRect;
	
    if(spriter && texture)
	{
		spriter->Begin(D3DXSPRITE_ALPHABLEND);
		bgRect.left = 0;
		bgRect.right = GetWindowWidth();
		bgRect.bottom = 900;
		bgRect.top = 900-offset;
		spriter->Draw(texture,&bgRect,NULL, &position, color);
		bgRect.top=0;
		bgRect.bottom=GetWindowHeight()-offset;
		D3DXVECTOR3 vecPosBG2(0,(float)offset,0);
		spriter->Draw(texture, &bgRect, NULL, &vecPosBG2, 0xFFFFFFFF);
		offset--;
		spriter->End();
	}
	gDevice->End();
	gDevice->Present();
}
