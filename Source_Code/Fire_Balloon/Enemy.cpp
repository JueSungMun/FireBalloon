#include "All_Header.h"

Enemy::Enemy(void) : Visible(true)
{
}

Enemy::~Enemy(void)
{
}

Enemy::Enemy(int setId) : Visible(true)
{
	id = setId;
}

void Enemy::initEnemy(RECT &inputX)
{
	Source.top= inputX.top;
	Source.bottom = inputX.bottom;
	Source.left = inputX.left;
	Source.right = inputX.right;
	Visible = TRUE;
	direction = TRUE;
	Position.x = 1;
	Position.y = 0;
	Position.z = 0;
	Center.x = 0;
	Center.y = 0;
	Center.z = 0;
	test_value =0;

	//Position.z = 1;
	ani_inverval =0;
}

BOOL Enemy::manageMoving(LPDIRECT3DDEVICE9 g_pd3dDevice, int offset)
{
	//cout<< id << "번째 새의 위치-> x:"<<Position.x<<" y:"<<Position.y <<endl;
	if(direction)
	{
		setTexture(g_pd3dDevice, _T(IMG_BIRD_RIGHT));
		sineMoving(offset);
		if(Position.x+40 >= SCREEN_WIDTH)
			direction=FALSE;
	}
	else
	{
		setTexture(g_pd3dDevice, _T(IMG_BIRD_LEFT));
		invSineMoving(offset);
		//if(Position.x+40 <= SCREEN_WIDTH)
		if(Position.x <= 0)
			direction=TRUE;
	}

	if(Position.y + BIRD_RECT_BOTTOM < 0 || Position.y > SCREEN_HEIGHT)
	{
		// 새의 위치가 위아래로 벗어나면 FALSE를 리턴하고 파괴시킴
		return FALSE; 
	}
	return TRUE;
}

void Enemy::sineMoving(int offset)
{
	Position.x += 2.0f;
	if(test_value%2==0)
	{
		Position.y = (float)(50*sin(Position.x*0.03)+offset) - (Position.x)/6;
		if(Position.x >= 207)
			test_value++;
	}
	else
	{
		Position.y = (float)(150*sin(Position.x*0.03)+offset) - (Position.x)/6;
	}
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
	Position.y = (float)(50*sin(Position.x*0.03)+offset) + (Position.x)/3;

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

int Enemy::getID()
{
	return id;
}

LPDIRECT3DTEXTURE9& Enemy::getTexture()
{
	return Texture;
}

BOOL Enemy::getVisible() const
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

void Enemy::setTexture(LPDIRECT3DDEVICE9 g_device, LPCWSTR img_source)
{
	D3DXCreateTextureFromFileEx( g_device, img_source, 
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &Texture); 
}