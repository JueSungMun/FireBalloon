#include "Manage_Scene.h"
#include "All_Header.h"

struct Image 
{
	BOOL Visible;
	LPDIRECT3DTEXTURE9 Texture;
	RECT Source;
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Center;
};

class GameScene : public Manage_Scene
{
private:
	int life;
	int currentEnemyNum;
	int currentScore;
	int currentStage;
	Image g_GoalLine;
	time_t startTime;
	time_t goalTime;
	time_t prevTimer;
	ObjectManager* om;
	D3DCOLOR color;
	LPD3DXSPRITE spriter;
	LPDIRECT3DTEXTURE9 balloonTexture;
	LPDIRECT3DTEXTURE9 backGroundTexture;
	LPCWSTR background;
	LPD3DXFONT scoreFont;
	LPD3DXFONT lifeFont;
	LPD3DXFONT stageFont;
	D3DXVECTOR3 position;
	D3DXVECTOR3 vecPosBG;
	D3DXVECTOR3 vecPosition;
	void InitStage(int stage);
public:
	GameScene();
	virtual ~GameScene();
	virtual void Initialize(HWND& hWnd);
	virtual void Draw(float gameTime, User& user);
};