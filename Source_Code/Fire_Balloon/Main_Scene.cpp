#include "Main_Scene.h"

Main_Scene::Main_Scene() : spriter(NULL), texture(NULL), pFont(NULL), windowWidth(600), windowHeight(700)
{ 
	position.x=0;
	position.y=0;
	position.z=0;

	color = D3DCOLOR_ARGB(255,255,255,255);
	background = _T("..\\Resource\\main_screen_background.jpg");
	SetSceneNumber(1);
	button = new Button(0,0,142,92);
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

	if (!SUCCEEDED(CreateWindow(_T("edit"), _T("EditBox"), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 0,
		400, 200, 25, hWnd, (HMENU) 100, NULL, NULL)))
	{
		MessageBox(NULL, _T("Generation error of Edit Box"), NULL, NULL);
	}

	/*
	if (!SUCCEEDED(btnWND = CreateWindow(_T("button"),_T("Click Me"),WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0,400,100,25,hWnd,(HMENU)0,NULL,NULL)))
	{
		MessageBox(NULL, _T("Generation error of Button"), NULL, NULL);
	}
	*/
}

bool Main_Scene::GenerateButton(int x, int y, int width, int height)
{
	/*
	WNDCLASSEX wcex;

	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = ButtonProc;
	wcex.hInstance = GetModuleHandle(NULL);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcex.lpszClassName = className;
	wcex.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if(!RegisterClassEx(&wcex))
	{
		return false;
	}

	hWnd = CreateWindow(className, windowTitle, WS_OVERLAPPEDWINDOW, x, y, width, height,
		NULL, NULL, wcex.hInstance, NULL );

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	return true;
	*/
}

void Main_Scene::Draw(float gameTime)
{
	gDevice->Clear(D3DCOLOR_XRGB(0,0,255));
	gDevice->Begin();

	RECT rcSrcRect;
	rcSrcRect.left = 0;
	rcSrcRect.right = windowWidth;
	rcSrcRect.bottom = windowHeight;
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
