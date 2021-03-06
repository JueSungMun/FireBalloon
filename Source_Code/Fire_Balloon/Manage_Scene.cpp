#include "Manage_Scene.h"

Manage_Scene::Manage_Scene() : sceneNumber(0) , isInitialed(false), windowWidth(600), windowHeight(700), isGameOver (false)
{

}

Manage_Scene::~Manage_Scene()
{
	if(gDevice)
	{
		delete gDevice;
		isInitialed = false;
		gDevice = NULL;
	}
}
int Manage_Scene::GetSceneNumber()
{
	return sceneNumber;
}

void Manage_Scene::SetSceneNumber(int num)
{
	sceneNumber = num;
}

void Manage_Scene::BeforeScene()
{
	sceneNumber--;
}

void Manage_Scene::NextScene()
{
	sceneNumber++;
}

void Manage_Scene::Initialize(HWND& hWnd)
{
	gDevice = new Graphic_Lib();
	
	if(!gDevice->Initilize(hWnd))
	{
		isInitialed = false;
	}
	else
	{
		isInitialed = true;
	}
	
}

void Manage_Scene::Run()
{
	float gameTime = 0.0f;
	Update(gameTime);
	Draw(gameTime);
}

void Manage_Scene::Update(float gameTime)
{
	//Update game sprites and logics
}

void Manage_Scene::Draw(float gameTime)
{
	gDevice->Clear(D3DCOLOR_XRGB(0,0,255));
	gDevice->Begin();


	gDevice->End();
	gDevice->Present();
}

void Manage_Scene::Draw(float gameTime, User& user)
{
	gDevice->Clear(D3DCOLOR_XRGB(0,0,255));
	gDevice->Begin();


	gDevice->End();
	gDevice->Present();
}

bool Manage_Scene::Initialized()
{
	return isInitialed;
}

LPCWSTR Manage_Scene::GetEditWindowText()
{
	LPCWSTR temp = _T("");
	return temp;
}

int Manage_Scene::GetWindowWidth()
{
	return windowWidth;
}

int Manage_Scene::GetWindowHeight()
{
	return windowHeight;
}

void Manage_Scene::SetGameOver(bool state)
{
	isGameOver = state;
}

bool Manage_Scene::GetGameState()
{
	return isGameOver;
}