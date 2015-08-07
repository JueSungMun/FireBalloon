#include "Main_Scene.h"

Main_Scene::Main_Scene() : spriter(NULL), texture(NULL)
{ 
	position.x=0;
	position.y=0;
	position.z=0;

	color = D3DCOLOR_ARGB(255,255,255,255);
	button.left = 100;
	button.top = 100;
	button.right = 300;
	button.bottom = 300;
	background = _T("..\\Resource\\main_screen_background.jpg");
	SetSceneNumber(1);
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
}

void Main_Scene::Initialize(HWND hWnd)
{
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
	}
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
	

    if(spriter && texture)
	{
		spriter->Begin(D3DXSPRITE_ALPHABLEND);
		spriter->Draw(texture,&rcSrcRect,NULL, &position, color);
		//spriter->Draw(NULL, &button, NULL, NULL, D3DCOLOR_ARGB(255,0,255,0));
		spriter->End();
	}

	gDevice->End();
	gDevice->Present();
	
}
