#include <d3dx9.h>
//#include <tchar.h>

class Button
{
private:
	RECT button;
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	//LPCWSTR file;
	D3DXVECTOR3 position;
	D3DCOLOR color;
	bool initialized;

public:
	Button(int x, int y, int width, int height);
	~Button();
	bool Initialize(LPDIRECT3DDEVICE9 device, LPWSTR file);
	bool IsInitialized();
	void Draw();
};
