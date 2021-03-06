#include "Main_Scene.h"

Main_Scene::Main_Scene() : spriter(NULL), texture(NULL), pFont(NULL)
{ 
	position.x=0;
	position.y=0;
	position.z=0;

	color = D3DCOLOR_ARGB(255,255,255,255);
	background = _T("..\\Resource\\main_screen_background.jpg");
	SetSceneNumber(MAIN_SCENE);
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
	DestroyWindow(btnWnd);
	DestroyWindow(hEditWnd);
}

void Main_Scene::Initialize(HWND& hWnd)
{
	if(!Manage_Scene::Initialized())
	{
		Manage_Scene::Initialize(hWnd);
	}
	
	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(gDevice->g_pd3dDevice, background, GetWindowWidth(), GetWindowHeight(), 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &texture)))
	{
		MessageBox(NULL,_T("Image Load error"),NULL,NULL);
	}
	
	if (!SUCCEEDED(D3DXCreateSprite(gDevice->g_pd3dDevice, &spriter)))
	{
		MessageBox(NULL,_T("Error on generating spriter"),NULL,NULL);
	}

	if (!SUCCEEDED(D3DXCreateFont(gDevice->g_pd3dDevice, 30,15, 255, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("���� ����"), &pFont)))
	{
		MessageBox(NULL, _T("Load Error of Font from the System"), NULL, NULL);
	}

	if (!SUCCEEDED(hEditWnd = CreateWindow(_T("edit"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 200, 400, 225, 25, hWnd, (HMENU) EDITBTN_ID, NULL, NULL)))
	{
		MessageBox(NULL, _T("Generation error of Edit Box"), NULL, NULL);
	}

	
	if (!SUCCEEDED(btnWnd = CreateWindow(_T("button"),_T("Ȯ��"),WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 450,400,100,25,hWnd,(HMENU)BUTTON_ID,NULL,NULL)))
	{
		MessageBox(NULL, _T("Generation error of Button"), NULL, NULL);
	}
	
}


void Main_Scene::Draw(float gameTime)
{
	gDevice->Clear(D3DCOLOR_XRGB(0,0,255));
	gDevice->Begin();

	RECT rcSrcRect;
	rcSrcRect.left = 0;
	rcSrcRect.right = GetWindowWidth();
	rcSrcRect.bottom = GetWindowHeight();
	rcSrcRect.top = 0;
	

	RECT textRect = {100,393,-1,-1};

    if(spriter && texture)
	{
		spriter->Begin(D3DXSPRITE_ALPHABLEND);
		spriter->Draw(texture,&rcSrcRect,NULL, &position, color);
		//spriter->Draw(NULL, &button, NULL, NULL, D3DCOLOR_ARGB(255,0,255,0));
		if(pFont)
			pFont->DrawText(spriter, _T("�г���"), -1, &textRect, DT_NOCLIP, D3DXCOLOR(1,1,1,1));
		spriter->End();
	}

	gDevice->End();
	gDevice->Present();
	
}

LPCWSTR Main_Scene::GetEditWindowText()
{
	LPWSTR str = new WCHAR[128];
	GetWindowText(hEditWnd, str, 128);
	return (LPCWSTR)str;
}