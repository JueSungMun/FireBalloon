/*
	그래픽 장치 생성 및 윈도우 핸들을 이용한 초기화

	1. 그림을 그리는 인터페이스 제공
*/

#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class Graphic_Lib
{
private:
	LPDIRECT3D9             g_pD3D;					 // Used to create the D3DDevice
	HRESULT InitD3D( HWND hWnd );
public:
	Graphic_Lib();
	~Graphic_Lib();
	LPDIRECT3DDEVICE9       g_pd3dDevice;			 // rendering device
	bool Initilize(HWND hWnd);
	void Clear (D3DCOLOR color);
	void Begin();
	void End();
	void Present();
};