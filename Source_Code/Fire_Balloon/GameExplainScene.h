#include "Manage_Scene.h"

class GameExplainScene : public Manage_Scene
{
private:
	int windowWidth;
	int windowHeight;
	D3DXVECTOR3 position;
	D3DCOLOR color;
	LPD3DXSPRITE spriter;
	LPDIRECT3DTEXTURE9 texture;
	LPCWSTR background;
public:
	GameExplainScene();
	~GameExplainScene();
	void Initialize(HWND& hWnd);
	void Draw(float gameTime);
};