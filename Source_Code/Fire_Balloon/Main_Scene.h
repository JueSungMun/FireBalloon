/*
	사용자가 본 게임전에 보는 첫화면.

*/

#include "Manage_Scene.h"

class Main_Scene : public Manage_Scene
{
private:
	D3DXVECTOR3 position;
	D3DCOLOR color;
	LPD3DXSPRITE spriter;
	LPDIRECT3DTEXTURE9 texture;
	LPCWSTR background;
	RECT button;
public:
	Main_Scene();
	Main_Scene(int windth, int height);
	~Main_Scene();
	void Initialize(HWND hWnd);
	void Draw(float gameTime);
};