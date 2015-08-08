#include "Button.h"

Button::Button(int x, int y, int width, int height)
{
	button.left = 0;
	button.right = width;
	button.top = 0;
	button.bottom = height;

	position.x = x;
	position.y = y;
	position.z = 0;

	color = D3DCOLOR_ARGB(255,255,255,255);
	//file = _T("..\\Resource\\confirm_button1.png");
	initialized = false;
}

bool Button::Initialize(LPDIRECT3DDEVICE9 device, LPWSTR file)
{
	/*
	if(!SUCCEEDED(D3DXCreateTextureFromFile(device,  file, &texture)))
	{
		return false;
	}
	*/

	if(!SUCCEEDED(D3DXCreateTextureFromFileEx(device, file, 
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, NULL, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, NULL, NULL, NULL, &texture)))
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
}