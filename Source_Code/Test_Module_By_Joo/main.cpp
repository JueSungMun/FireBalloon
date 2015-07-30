#include <iostream>
#include "Graphic_Lib.h"
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

	Graphic_Lib dl;
	dl.Initilize();
	dl.LoadTexture(BACKGROUND_TEXTURE);
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
			dl.Draw();
			dl.PlayTheMusic();
		}
		//dl.PlayTheMusic();
	}
	
    return 0; 
}