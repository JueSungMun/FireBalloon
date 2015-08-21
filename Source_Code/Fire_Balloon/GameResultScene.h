#include "Manage_Scene.h"

class GameResultScene : public Manage_Scene
{
private:
	D3DXVECTOR3 position;
	D3DCOLOR color;
	LPD3DXSPRITE spriter;
	LPDIRECT3DTEXTURE9 texture;
	LPCWSTR background;
	LPD3DXFONT scoreFont;
	LPD3DXFONT lifeFont;
	LPD3DXFONT stageFont;
	LPD3DXFONT nameFont;
public:
	GameResultScene();
	virtual ~GameResultScene();
	virtual void Initialize(HWND& hWnd);
	virtual void Draw(float gameTime, User& user);
};