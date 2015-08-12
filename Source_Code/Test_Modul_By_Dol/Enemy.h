#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class Enemy
{
private:
	BOOL Visible;
	LPDIRECT3DTEXTURE9 Texture;
	RECT Source;
	D3DXVECTOR3 Position;
	const D3DXVECTOR3 Center;

public:
	Enemy(void);
	~Enemy(void);
	void initEnemy(RECT);
	void setTexture(LPDIRECT3DDEVICE9, const char* );
	void setSource(RECT);
	void setVisible(BOOL);
	void setPosition(D3DXVECTOR3);
	void setCenter(const D3DXVECTOR3);

	BOOL getVisible();
	LPDIRECT3DTEXTURE9 getTexture();
	RECT* getSource();
	D3DXVECTOR3* getPosition();
	const D3DXVECTOR3* getCenter();

	void sineMoving(int);
	void invSineMoving(int);
};

