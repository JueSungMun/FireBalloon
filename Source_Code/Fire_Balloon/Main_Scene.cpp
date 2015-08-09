#include "Main_Scene.h"

Main_Scene::Main_Scene() : spriter(NULL), texture(NULL), pFont(NULL)
{ 
	position.x=0;
	position.y=0;
	position.z=0;

	color = D3DCOLOR_ARGB(255,255,255,255);
	background = _T("..\\Resource\\main_screen_background.jpg");
	SetSceneNumber(1);
	button = new Button(300,300,142,92);
}

Main_Scene::Main_Scene(int width, int height)
{

}

Main_Scene::~Main_Scene()
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
	if(pFont != NULL)
	{
		pFont->Release();
		pFont = 0;
	}
}

void Main_Scene::Initialize(HWND& hWnd)
{
	if(!Manage_Scene::Initialized())
	{
		Manage_Scene::Initialize(hWnd);
	}
	
	if (!SUCCEEDED(D3DXCreateTextureFromFile(gDevice->g_pd3dDevice, background, &texture)))
	{
		MessageBox(NULL,_T("Image Load error"),NULL,NULL);
	}
	
	if (!SUCCEEDED(D3DXCreateSprite(gDevice->g_pd3dDevice, &spriter)))
	{
		MessageBox(NULL,_T("Error on generating spriter"),NULL,NULL);
	}

	if (!SUCCEEDED(button->Initialize(gDevice->g_pd3dDevice, _T("..\\Resource\\confirm_button1.png"))))
	{
		MessageBox(NULL,_T("Load Error of Button texture"),NULL,NULL);
	}
				
	if (!SUCCEEDED(D3DXCreateFont(gDevice->g_pd3dDevice, 40,30, 255, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("¹ÙÅÁÃ¼"), &pFont)))
	{
		MessageBox(NULL, _T("Load Error of Font from the System"), NULL, NULL);
	}

	if (!SUCCEEDED(CreateWindow(_T("edit"), _T("EditBox"), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, (GetSystemMetrics(SM_CXSCREEN)-600)/2,
		(GetSystemMetrics(SM_CYSCREEN)-600)/2, 200, 25, hWnd, (HMENU) 100, NULL, NULL)))
	{
		MessageBox(NULL, _T("Generation error of Edit Box"), NULL, NULL);
	}

	//ShowWindow(hEditWND, SW_SHOWDEFAULT);
	/*
	if(Initialized())
	{
		if (!SUCCEEDED(D3DXCreateTextureFromFile(gDevice->g_pd3dDevice, background, &texture)))
		{
			MessageBox(NULL,_T("Image Load error"),NULL,NULL);
		}
	
		if (!SUCCEEDED(D3DXCreateSprite(gDevice->g_pd3dDevice, &spriter)))
		{
			MessageBox(NULL,_T("Error on generating spriter"),NULL,NULL);
		}

		if (!SUCCEEDED(button->Initialize(gDevice->g_pd3dDevice, _T("..\\Resource\\confirm_button1.png"))))
		{
			MessageBox(NULL,_T("Load Error of Button texture"),NULL,NULL);
		}
				
		if (!SUCCEEDED(D3DXCreateFont(gDevice->g_pd3dDevice, 40,30, 255, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("¹ÙÅÁÃ¼"), &pFont)))
		{
			MessageBox(NULL, _T("Load Error of Font from the System"), NULL, NULL);
		}

		if (!SUCCEEDED(CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 10, 10, 200, 25, hWnd, (HMENU) 100, NULL, NULL)))
		{
			MessageBox(NULL, _T("Generation error of Edit Box"), NULL, NULL);
		}

		ShowWindow(hEditWND, SW_SHOWDEFAULT);
	}
	else
	{
		Manage_Scene::Initialize(hWnd);

		if (!SUCCEEDED(D3DXCreateTextureFromFile(gDevice->g_pd3dDevice, background, &texture)))
		{
			MessageBox(NULL,_T("Image Load error"),NULL,NULL);
		}
	
		if (!SUCCEEDED(D3DXCreateSprite(gDevice->g_pd3dDevice, &spriter)))
		{
			MessageBox(NULL,_T("Error on generating spriter"),NULL,NULL);
		}
		
		if (!SUCCEEDED(button->Initialize(gDevice->g_pd3dDevice, _T("..\\Resource\\confirm_button1.png"))))
		{
			MessageBox(NULL,_T("Load Error of Button texture"),NULL,NULL);
		}

		if (!SUCCEEDED(D3DXCreateFont(gDevice->g_pd3dDevice, 40,30, 255, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("¹ÙÅÁÃ¼"), &pFont)))
		{
			MessageBox(NULL, _T("Load Error of Font from the System"), NULL, NULL);
		}

		if (!SUCCEEDED(CreateWindow(_T("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 10, 10, 200, 25, hWnd, (HMENU) 100, NULL, NULL)))
		{
			MessageBox(NULL, _T("Generation error of Edit Box"), NULL, NULL);
		}

		ShowWindow(hEditWND, SW_SHOWDEFAULT);
	}
	*/
}

void Main_Scene::Draw(float gameTime)
{
	gDevice->Clear(D3DCOLOR_XRGB(0,0,255));
	gDevice->Begin();

	RECT rcSrcRect;
	rcSrcRect.left = 0;
	rcSrcRect.right = 600;
	rcSrcRect.bottom = 600;
	rcSrcRect.top = 0;
	

	RECT textRect = {20,30,-1,-1};

    if(spriter && texture)
	{
		spriter->Begin(D3DXSPRITE_ALPHABLEND);
		spriter->Draw(texture,&rcSrcRect,NULL, &position, color);
		//spriter->Draw(NULL, &button, NULL, NULL, D3DCOLOR_ARGB(255,0,255,0));
		if(pFont)
			pFont->DrawText(spriter, _T("Test"), -1, &textRect, DT_NOCLIP, D3DXCOLOR(0,0,0,1));
		spriter->End();
	}

	if(button->IsInitialized())
	{
		button->Draw();
	}

	gDevice->End();
	gDevice->Present();
	
}
