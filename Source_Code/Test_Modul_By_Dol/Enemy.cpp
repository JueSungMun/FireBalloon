#include "Enemy.h"

Enemy::Enemy(void)
{
}

Enemy::~Enemy(void)
{
}

void Enemy::initEnemy(RECT inputX)
{
	Source.top= inputX.top;
	Source.bottom = inputX.bottom;
	Source.left = inputX.left;
	Source.right = inputX.right;
	Visible = TRUE;
	Position.x = 1;
	Position.y = 0;
	ani_inverval =0;
}

void Enemy::sineMoving(int offset)
{
	
	Position.x += 2.0f;
	Position.y = (float)(50*sin(Position.x*0.03)+offset);

	ani_inverval++;
	if(ani_inverval%5==0)
		if(Source.bottom < 306)
		{
			Source.top+=51;
			Source.bottom+=51;
		}
		else
		{
			Source.top =0;
			Source.bottom=51;
		}
}

void Enemy::invSineMoving(int offset)
{
	Position.x -= 2.0f;
	Position.y = (float)(50*sin(Position.x*0.03)+offset);

	ani_inverval++;
	if(ani_inverval%5==0)
		if(Source.bottom < 306)
		{
			Source.top+=51;
			Source.bottom+=51;
		}
		else
		{
			Source.top =0;
			Source.bottom=51;
		}
}

LPDIRECT3DTEXTURE9 Enemy::getTexture()
{
	return Texture;
}

BOOL Enemy::getVisible()
{
	return Visible;
}

RECT* Enemy::getSource()
{
	return &Source;
}

D3DXVECTOR3* Enemy::getPosition() 
{
	return &Position;
}

const D3DXVECTOR3* Enemy::getCenter()
{
	return &Center;
}

void Enemy::setSource(RECT rct)
{
	Source.bottom = rct.bottom;
	Source.top = rct.top;
	Source.left = rct.left;
	Source.right = rct.right;
}

void Enemy::setPosition(D3DXVECTOR3 pos)
{
	Position.x = pos.x;
	Position.y = pos.y;
}

void Enemy::setCenter(D3DXVECTOR3 cent)
{
	
}

void Enemy::setVisible(BOOL isVisible)
{
	Visible = isVisible;
}
void Enemy::setTexture(LPDIRECT3DDEVICE9 g_device, const char* img_source)
{
	D3DXCreateTextureFromFileEx( g_device, img_source, 
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &Texture); 
}