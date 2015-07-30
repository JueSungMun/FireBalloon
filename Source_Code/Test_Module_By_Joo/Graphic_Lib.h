#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define AUDIO_RESOURCE  "..\\Resource\\Audio\\lol.wav" 
#include "Audio.h"

class Graphic_Lib
{
private:
	LPDIRECT3D9             g_pD3D;					 // Used to create the D3DDevice
	LPDIRECT3DDEVICE9       g_pd3dDevice;			 // rendering device
	LPD3DXSPRITE g_pSprite;
	WNDCLASSEX g_wc;
	HWND g_hWnd;
	Audio audio;
	LPDIRECT3DTEXTURE9 backGroundTexture;
	
	void InitWin(void);
	void InitWin(LPCWSTR windowName, int posX, int posY, int width, int height);
	void InitDX(void);
	static LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	HRESULT InitD3D( HWND hWnd );
	VOID Cleanup();
public:
	Graphic_Lib();
	Graphic_Lib(LPCWSTR windowName, int posX, int posY, int width, int height);
	~Graphic_Lib();
	void Initilize(void);
	void LoadTexture(LPCWSTR img);
	void ShowTheWindow();
	VOID Draw();
	WNDCLASSEX GetValueGWC();
	void PlayTheMusic();
	void LoadTheMusic();
};