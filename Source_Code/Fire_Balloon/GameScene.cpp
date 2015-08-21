#include "GameScene.h"

GameScene::GameScene() : spriter(NULL), balloonTexture(NULL), backGroundTexture(NULL),
	life(200), currentScore(0), currentEnemyNum(0), currentStage(1), prevTimer(0)
{ 
	//배경위치 초기화
	//position.x=0;
	//position.y=0;
	//position.z=0;
	//vecPosBG.x = 0;
	//vecPosBG.y = 0;
	//vecPosBG.z = 0;
	//vecPosition.x = SCREEN_WIDTH/2;
	//vecPosition.y = SCREEN_HEIGHT/8;
	//vecPosition.z = 0;

	color = D3DCOLOR_ARGB(255,255,255,255);
	background = _T("..\\Resource\\bird_test\\background.png");
	SetSceneNumber(GAME_SCENE);
	//ZeroMemory(&om, sizeof(ObjectManager));
	//om = new ObjectManager;
	//startTime = 0;
	//goalTime = 0;
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

void GameScene::InitStage(int stage)
{
	//유저 위치 초기화
	vecPosition.x = SCREEN_WIDTH/2;
	vecPosition.y = SCREEN_HEIGHT/8;
	vecPosition.z = .0f;
	
	//배경 위치 초기화
	vecPosBG.x = .0f;
	vecPosBG.y = .0f;
	vecPosBG.z = .0f;

	//골라인 초기화
	g_GoalLine.Source.left = 0;
	g_GoalLine.Source.top = 0;
	g_GoalLine.Source.right = 600;
	g_GoalLine.Source.bottom = 40;
	g_GoalLine.Visible = TRUE;
	g_GoalLine.Position.x = 0;
	g_GoalLine.Position.y = 700;
	om = new ObjectManager(stage);
	//종료시간 초기화
	
	time(&startTime);
	goalTime = startTime + (3*stage);
}
void GameScene::Initialize(HWND& hWnd)
{
	if(!Manage_Scene::Initialized())
	{
		Manage_Scene::Initialize(hWnd);
	}
	
	/*
	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(gDevice->g_pd3dDevice, background, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &backGroundTexture)))
	{
		MessageBox(NULL,_T("Image Load error"),NULL,NULL);
	}
	*/
	ZeroMemory(&g_GoalLine, sizeof(g_GoalLine));
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
	
	InitStage(1);
}


void GameScene::Draw(float gameTime, User& user)
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
	
	if( currentEnemyNum < om->ManageMaxEnemy() )
	{
		if(GetTickCount()%60==0)
		{
			om->insertObj();
			currentEnemyNum++;
		}
	}
	
	if ((GetKeyState(VK_LEFT) & 0x80000000) && vecPosition.x > 0) 	
			vecPosition.x -= 7.0f;
	if ((GetKeyState(VK_RIGHT) & 0x80000000) && vecPosition.x+rcSrcRect.right < SCREEN_WIDTH) 
		vecPosition.x += 7.0f;
	if ((GetKeyState(VK_UP) & 0x80000000) && vecPosition.y > 0 ) 
		vecPosition.y -= 5.0f;
	if ((GetKeyState(VK_DOWN) & 0x80000000) && vecPosition.y+rcSrcRect.bottom < SCREEN_HEIGHT) 	
		vecPosition.y += 10.0f;

	// 충돌체크
	// 보이는 적중에 부딪히면 파괴
	if(currentEnemyNum>=0)
	{	
		for(int i=0; i<om->ManageMaxEnemy(); i++)
			if(om->getAlive(i))
			{
				if( !(om->getEnemy(i).manageMoving(gDevice->g_pd3dDevice, i*100+100)) ) 
				{
					//새의 위치가 위아래로 벗어나면 파괴
					om->deleteObj(i);
					currentEnemyNum--;
				} 
				else 
				{
					// 충돌체크 보이는 적중에 부딪히면 파괴		
					D3DXVECTOR3* pos = om->getEnemy(i).getPosition();
					if( vecPosition.x < pos->x + BIRD_RECT_RIGHT
						&&pos->x < vecPosition.x + rcSrcRect.right
						&&vecPosition.y < pos->y + BIRD_RECT_BOTTOM
						&&pos->y < vecPosition.y + rcSrcRect.bottom)
					{	
						currentScore -= 50;
						if(currentScore < 0)
							currentScore =0;							
						life -= 10;
						om->deleteObj(i);
						currentEnemyNum--;
					}	
				}
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
		bgRect.right = SCREEN_WIDTH;
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
		if(goalTime < crtTime)
		{
			g_GoalLine.Position.y -= 3.0f;
			spriter->Draw( g_GoalLine.Texture, &g_GoalLine.Source, &g_GoalLine.Center, &g_GoalLine.Position, 0xffffffff );
		}
		
		if(currentEnemyNum > 0)
		{
			for(int i=0; i<om->ManageMaxEnemy(); i++)
			{
				if(om->getAlive(i) == TRUE)
					spriter->Draw( om->getEnemy(i).getTexture(), om->getEnemy(i).getSource(), om->getEnemy(i).getCenter(), om->getEnemy(i).getPosition(), 0xffffffff );
			}
		}

		// 골라인과 플레이어가 만나면 
		if ( g_GoalLine.Position.y < vecPosition.y )
		{
			if(currentStage == 5)
			{
				// 스테이지 클리어
				user.SetScore(currentScore);
				user.SetStage(currentStage);
				user.SetUserState(user.GAME_CLEAR);
				SetGameOver(true);
				//MessageBox(NULL, _T("ALL STAGE CLEAR!, Congraturations!"), NULL, MB_OK);
				//exit(0);
			}
			currentStage++;
			delete om;
			InitStage(currentStage);
		}

		spriter->Draw(balloonTexture, &rcSrcRect, &vecCenter, &vecPosition, 0xffffffff);

		RECT scoreRect = {400,20,-1,-1};
		RECT lifeRect = {20,20,-1,-1};
		RECT stageRect = {220,20,-1,-1};
		
		if(prevTimer == NULL)
			prevTimer = crtTime;
		if(crtTime-prevTimer != 0)
		{
			currentScore+=5;
		}
		prevTimer = crtTime;

		std::string scoreStr = "SCORE ";
		scoreStr.append(std::to_string(currentScore));

		std::string lifeStr = "LIFE ";
		lifeStr.append(std::to_string(life));

		std::string stageStr = "STAGE ";
		stageStr.append(std::to_string(om->GetStageNumber()));

		std::wstring scoreWstr = std::wstring(scoreStr.begin(), scoreStr.end());
		std::wstring lifeWstr = std::wstring(lifeStr.begin(), lifeStr.end());
		std::wstring stageWstr = std::wstring(stageStr.begin(), stageStr.end());
		//LPCWSTR scoreResult = _T(scoreStr.c_str());
		if(scoreFont)
			scoreFont->DrawText(spriter, scoreWstr.c_str(), scoreWstr.length(), &scoreRect, DT_NOCLIP, D3DXCOLOR(0,0,0,1));

		if(lifeFont)
			lifeFont->DrawText(spriter, lifeWstr.c_str(), lifeWstr.length(), &lifeRect,DT_NOCLIP, D3DXCOLOR(0,0,0,1));
		if(stageFont)
			stageFont->DrawText(spriter, stageWstr.c_str(), stageWstr.length(), &stageRect, DT_NOCLIP, D3DXCOLOR(0,0,0,1));
	
		spriter->End();
	}
	//else
		//MessageBox(NULL, _T("Error"), NULL, NULL);
	gDevice->End();
	gDevice->Present();
}
