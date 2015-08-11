#include "Manage_Scene.h"

class GameScene : public Manage_Scene
{
private:
	D3DXVECTOR3 position;
	D3DCOLOR color;
	LPD3DXSPRITE spriter;
	LPDIRECT3DTEXTURE9 texture;
	LPCWSTR background;
public:
	GameScene();
	~GameScene();
	void Initialize(HWND& hWnd);
	void Draw(float gameTime);
};