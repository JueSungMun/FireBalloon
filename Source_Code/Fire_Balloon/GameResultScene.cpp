#include "GameResultScene.h"

GameResultScene::GameResultScene() : spriter(NULL), texture(NULL)
{ 
	position.x=0;
	position.y=0;
	position.z=0;

	color = D3DCOLOR_ARGB(255,255,255,255);
	background = NULL;//_T("..\\Resource\\game_explain_view.png");
	SetSceneNumber(GAME_RESULT_SCENE);
}

GameResultScene::~GameResultScene()
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

void GameResultScene::Initialize(HWND& hWnd)
{
	if(!Manage_Scene::Initialized())
	{
		Manage_Scene::Initialize(hWnd);
	}
	
	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(gDevice->g_pd3dDevice, background, GetWindowWidth(), GetWindowHeight(), 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &texture)))
	{
		//MessageBox(NULL,_T("Image Load error"),NULL,NULL);
	}
	
	if (!SUCCEEDED(D3DXCreateSprite(gDevice->g_pd3dDevice, &spriter)))
	{
		MessageBox(NULL,_T("Error on generating spriter"),NULL,NULL);
	}

	D3DXCreateFont(gDevice->g_pd3dDevice, 30,15, 255, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("¹ÙÅÁÃ¼"), &scoreFont);
	D3DXCreateFont(gDevice->g_pd3dDevice, 30,15, 255, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("¹ÙÅÁÃ¼"), &lifeFont);
	D3DXCreateFont(gDevice->g_pd3dDevice, 30,15, 255, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("¹ÙÅÁÃ¼"), &stageFont);
	D3DXCreateFont(gDevice->g_pd3dDevice, 30,15, 255, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("¹ÙÅÁÃ¼"), &nameFont);
}


void GameResultScene::Draw(float gameTime, User& user)
{
	gDevice->Clear(D3DCOLOR_XRGB(0,0,0));
	gDevice->Begin();

	RECT rcSrcRect;
	rcSrcRect.left = 0;
	rcSrcRect.right = GetWindowWidth();
	rcSrcRect.bottom = GetWindowHeight();
	rcSrcRect.top = 0;
	
    if(spriter)
	{
		spriter->Begin(D3DXSPRITE_ALPHABLEND);
		spriter->Draw(texture,&rcSrcRect,NULL, &position, color);
		RECT nameRect = {20,20,-1,-1};	
		RECT scoreRect = {20,200,-1,-1};
		RECT stageRect = {20,400,-1,-1};

		std::string scoreStr = "SCORE ";
		scoreStr.append(std::to_string(user.GetScore()));

		std::string stageStr = "STAGE ";
		stageStr.append(std::to_string(user.GetStageState()));

		std::string nameStr = "Name ";

		std::wstring scoreWstr = std::wstring(scoreStr.begin(), scoreStr.end());
		std::wstring stageWstr = std::wstring(stageStr.begin(), stageStr.end());
		std::wstring nameWstr = std::wstring(nameStr.begin(), nameStr.end());
		nameWstr.append(user.GetName());

		//LPCWSTR scoreResult = _T(scoreStr.c_str());
		if(nameFont)
			lifeFont->DrawText(spriter, nameWstr.c_str(), nameWstr.length(), &nameRect, DT_NOCLIP, D3DXCOLOR(1,1,1,1));

		if(scoreFont)
			scoreFont->DrawText(spriter, scoreWstr.c_str(), scoreWstr.length(), &scoreRect, DT_NOCLIP, D3DXCOLOR(1,1,1,1));
			
		if(stageFont)
			stageFont->DrawText(spriter, stageWstr.c_str(), stageWstr.length(), &stageRect, DT_NOCLIP, D3DXCOLOR(1,1,1,1));

		spriter->End();
	}
	
	gDevice->End();
	gDevice->Present();
	
}
