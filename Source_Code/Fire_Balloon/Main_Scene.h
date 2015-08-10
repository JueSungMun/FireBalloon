/*
	사용자가 본 게임전에 보는 첫화면.

*/

#include "Manage_Scene.h"
#include "Button.h"

class Main_Scene : public Manage_Scene
{
private:
	int windowWidth;
	int windowHeight;
	D3DXVECTOR3 position;
	D3DCOLOR color;
	LPD3DXSPRITE spriter;
	LPD3DXFONT pFont;
	HWND btnWND;
	HWND hEditWND;
	LPDIRECT3DTEXTURE9 texture;
	LPCWSTR background;
	Button* button;
public:
	Main_Scene();
	Main_Scene(int windth, int height);
	~Main_Scene();
	void Initialize(HWND& hWnd);
	void Draw(float gameTime);
	bool GenerateButton(int x, int y, int width, int height);
	LRESULT CALLBACK ButtonProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};