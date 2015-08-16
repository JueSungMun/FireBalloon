#include "Manage_Scene.h"

class GameExplainScene : public Manage_Scene
{
private:
	D3DXVECTOR3 position;
	D3DCOLOR color;
	LPD3DXSPRITE spriter;
	LPDIRECT3DTEXTURE9 texture;
	LPCWSTR background;
public:
	GameExplainScene();
	virtual ~GameExplainScene();
	virtual void Initialize(HWND& hWnd);
	virtual void Draw(float gameTime);
};