#include <iostream>
#include "DirectX_Lib.h"
#define BACKGROUND_TEXTURE _T("..\\Resource\\main_screen_background.jpg")

using namespace std;
//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	LPCWSTR Class_Name = _T("Main Scene");
	//Class_Name = _T("Next Scene");

	DirectX_Lib dl;
	dl.Initilize();
	dl.LoadBackGroundData(BACKGROUND_TEXTURE);
	dl.ShowTheWindow();
	dl.LoadTheMusic();
	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );
	while( msg.message!=WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			dl.Render();
			dl.PlayTheMusic();
		}
		//dl.PlayTheMusic();
	}
	
	UnregisterClass( _T("D3D Tutorial"), dl.GetValueGWC().hInstance );
    return 0; 
}