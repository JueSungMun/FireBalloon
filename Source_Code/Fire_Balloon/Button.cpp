#include "Button.h"

Button::Button(int x, int y, int width, int height)
{
	button.left = x;
	button.right = x+width;
	button.top = y;
	button.bottom = y+height;

	position.x = 0;
	position.y = 0;
	position.z = 0;

	color = D3DCOLOR_ARGB(255,0,255,0);

	initialized = false;
}

bool Button::Initialize(LPDIRECT3DDEVICE9 device, LPWSTR file)
{
	if(!SUCCEEDED(D3DXCreateTextureFromFile(device,  file, &texture)))
	{
		return false;
	}

	if(!SUCCEEDED(D3DXCreateSprite(device, &sprite)))
	{
		return false;
	}
	initialized = true;
	return true;
}

bool Button::IsInitialized()
{
	return initialized;
}

void Button::Draw()
{
	if(sprite&& texture)
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(texture, &button, NULL, &position, color);
		sprite->End();
	}
	else
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(NULL, &button, NULL, &position, color);
		sprite->End();
	}
}