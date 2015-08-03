//http://gamedev.stackexchange.com/questions/45585/directx-9-0c-and-c-gui
#include <Windows.h>

class Button
{
	private:
		RECT rect;
	public:
		Button(RECT rect);
		bool RectCollision(RECT rectA, RECT rectB);
		bool CheckForButtonPress(HWND hwnd);
};