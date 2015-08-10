#include "GameExplainScene.h"

GameExplainScene::GameExplainScene() : spriter(NULL), texture(NULL), windowWidth(600), windowHeight(700)
{ 
	position.x=0;
	position.y=0;
	position.z=0;

	color = D3DCOLOR_ARGB(255,255,255,255);
	background = _T("..\\Resource\\game_explain_view.png");
	SetSceneNumber(2);
}

GameExplainScene::~GameExplainScene()
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

void GameExplainScene::Initialize(HWND& hWnd)
{
	if(!Manage_Scene::Initialized())
	{
		Manage_Scene::Initialize(hWnd);
	}
	
	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(gDevice->g_pd3dDevice, background, windowWidth, windowHeight, 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &texture)))
	{
		MessageBox(NULL,_T("Image Load error"),NULL,NULL);
	}
	
	if (!SUCCEEDED(D3DXCreateSprite(gDevice->g_pd3dDevice, &spriter)))
	{
		MessageBox(NULL,_T("Error on generating spriter"),NULL,NULL);
	}
}


void GameExplainScene::Draw(float gameTime)
{
	gDevice->Clear(D3DCOLOR_XRGB(0,0,255));
	gDevice->Begin();

	RECT rcSrcRect;
	rcSrcRect.left = 0;
	rcSrcRect.right = windowWidth;
	rcSrcRect.bottom = windowHeight;
	rcSrcRect.top = 0;
	
    if(spriter && texture)
	{
		spriter->Begin(D3DXSPRITE_ALPHABLEND);
		spriter->Draw(texture,&rcSrcRect,NULL, &position, color);
		spriter->End();
	}

	
	gDevice->End();
	gDevice->Present();
	
}
