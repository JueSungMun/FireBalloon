#include "GameScene.h"

GameScene::GameScene() : spriter(NULL), balloonTexture(NULL), backGroundTexture(NULL), life(200), currentScore(0)
{ 
	position.x=0;
	position.y=0;
	position.z=0;
	vecPosBG.x = 0;
	vecPosBG.y = 0;
	vecPosBG.z = 0;
	vecPosition.x = SCREEN_WIDTH/2;
	vecPosition.y = SCREEN_HEIGHT/8;
	vecPosition.z = 0;

	color = D3DCOLOR_ARGB(255,255,255,255);
	//background = _T("..\\Resource\\bird_test\\background.png");
	SetSceneNumber(3);
	ZeroMemory(&om, sizeof(ObjectManager));
	om = new ObjectManager;
	startTime = 0;
	goaltime = 0;
}

GameScene::~GameScene()
{
	if(spriter != NULL)
	{
		spriter->Release();
		spriter=0;
	}
	if(balloonTexture != NULL)
	{
		balloonTexture->Release();
		balloonTexture = 0;
	}
	if(backGroundTexture != NULL)
	{
		backGroundTexture->Release();
		backGroundTexture = 0;
	}
}

void GameScene::Initialize(HWND& hWnd)
{
	if(!Manage_Scene::Initialized())
	{
		Manage_Scene::Initialize(hWnd);
	}
	
	//객체 매니저 초기화
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

	// 골라인 초기화
	ZeroMemory(&g_GoalLine, sizeof(g_GoalLine));
	g_GoalLine.Source.left=0;
	g_GoalLine.Source.top=0;
	g_GoalLine.Source.right = 600;
	g_GoalLine.Source.bottom = 40;
	g_GoalLine.Visible = TRUE;
	g_GoalLine.Position.x = 0;
	g_GoalLine.Position.y = 700;
	g_GoalLine.Position.z = 0;

	time(&startTime);
	goaltime = startTime+10;

	/*
	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(gDevice->g_pd3dDevice, background, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &backGroundTexture)))
	{
		MessageBox(NULL,_T("Image Load error"),NULL,NULL);
	}
	*/
	
	D3DXCreateTextureFromFileEx(gDevice->g_pd3dDevice, _T(IMG_FIREBALLOON), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &balloonTexture);
	D3DXCreateTextureFromFileEx(gDevice->g_pd3dDevice, _T(IMG_BG), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &backGroundTexture); 
	D3DXCreateTextureFromFileEx(gDevice->g_pd3dDevice, _T(IMG_GOALLINE), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &g_GoalLine.Texture); 
	D3DXCreateFont(gDevice->g_pd3dDevice, 30,15, 255, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("바탕체"), &scoreFont);
	D3DXCreateFont(gDevice->g_pd3dDevice, 30,15, 255, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("바탕체"), &lifeFont);
	D3DXCreateFont(gDevice->g_pd3dDevice, 30,15, 255, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("바탕체"), &stageFont);

	if (!SUCCEEDED(D3DXCreateSprite(gDevice->g_pd3dDevice, &spriter)))
	{
		MessageBox(NULL,_T("Error on generating spriter"),NULL,NULL);
	}
}


void GameScene::Draw(float gameTime)
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
	
	
	om->getEnemy(0).manageMoving(gDevice->g_pd3dDevice, 100);
	om->getEnemy(1).manageMoving(gDevice->g_pd3dDevice, 200);
	om->getEnemy(2).manageMoving(gDevice->g_pd3dDevice, 300);

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
		MessageBox(NULL, _T("Oops! ,You are dead!"), NULL, MB_OK);
		exit(1);
	}
	
	gDevice->Clear(D3DCOLOR_XRGB(0,0,255));
	gDevice->Begin();

	if(spriter != NULL && balloonTexture != NULL && backGroundTexture!= NULL)
	{
		spriter->Begin(D3DXSPRITE_ALPHABLEND);

		bgRect.left = 0;
		bgRect.right = 600;
		bgRect.top = 0;
		bgRect.bottom = SCREEN_HEIGHT;
		vecPosBG.y = -(float)offset;
		spriter->Draw(backGroundTexture, &bgRect, NULL, &vecPosBG, 0xFFFFFFFF);

		bgRect.top = 0;
		bgRect.bottom = offset;
		
		D3DXVECTOR3 vecPosBG2(0,(float)(SCREEN_HEIGHT-offset),0);
		spriter->Draw(backGroundTexture, &bgRect, NULL, &vecPosBG2, 0xFFFFFFFF);
		offset++;
		offset = offset%SCREEN_HEIGHT;

		//시작하고 10초뒤에 골라인 올라옴
		time_t crtTime;
		time(&crtTime);
		if(goaltime < crtTime)
		{
			g_GoalLine.Position.y -= 3.0f;
			spriter->Draw( g_GoalLine.Texture, &g_GoalLine.Source, &g_GoalLine.Center, &g_GoalLine.Position, 0xffffffff );
		}
		
		for(int i=0; i<MAX_ENEMY; i++)
		{
			if(om->getEnemy(i).getVisible() == TRUE)
				spriter->Draw( om->getEnemy(i).getTexture(), om->getEnemy(i).getSource(), om->getEnemy(i).getCenter(), om->getEnemy(i).getPosition(), 0xffffffff );
		}
		// 골라인과 플레이어가 만나면 
		if ( g_GoalLine.Position.y < vecPosition.y )
		{
			// 스테이지 클리어
			MessageBox(NULL, _T("STAGE CLEAR!, Congraturations!"), NULL, MB_OK);
			exit(0);
		}

		spriter->Draw(balloonTexture, &rcSrcRect, &vecCenter, &vecPosition, 0xffffffff);

		RECT scoreRect = {400,20,-1,-1};
		RECT lifeRect = {20,20,-1,-1};

		std::string scoreStr = "SCORE ";
		scoreStr.append(std::to_string((crtTime-startTime)*10+currentScore));

		std::string lifeStr = "LIFE ";
		lifeStr.append(std::to_string(life));

		std::wstring scoreWstr = std::wstring(scoreStr.begin(), scoreStr.end());
		std::wstring lifeWstr = std::wstring(lifeStr.begin(), lifeStr.end());
		//LPCWSTR scoreResult = _T(scoreStr.c_str());
		if(scoreFont)
			scoreFont->DrawText(spriter, scoreWstr.c_str(), scoreStr.length(), &scoreRect, DT_NOCLIP, D3DXCOLOR(0,0,0,1));

		if(lifeFont)
			lifeFont->DrawText(spriter, lifeWstr.c_str(), lifeStr.length(), &lifeRect,DT_NOCLIP, D3DXCOLOR(0,0,0,1));
	
		spriter->End();
	}
	//else
		//MessageBox(NULL, _T("Error"), NULL, NULL);
	gDevice->End();
	gDevice->Present();


	/*
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
	*/
}
