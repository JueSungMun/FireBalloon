/*
	사용자가 본 게임전에 보는 첫화면.

*/

#include "Manage_Scene.h"
#include "Button.h"
#include <atlbase.h>

class Main_Scene : public Manage_Scene
{
private:
	HWND btnWnd;
	HWND hEditWnd;
	D3DXVECTOR3 position;
	D3DCOLOR color;
	LPD3DXSPRITE spriter;
	LPD3DXFONT pFont;
	LPDIRECT3DTEXTURE9 texture;
	LPCWSTR background;
	Button* button;
public:
	Main_Scene();
	Main_Scene(int windth, int height);
	virtual ~Main_Scene();
	virtual void Initialize(HWND& hWnd);
	virtual void Draw(float gameTime);
	virtual LPCWSTR GetEditWindowText();
};