#include <Windows.h>
#include "Main_Scene.h"

bool GenerateWindow(LPCWSTR className, LPCWSTR windowTitle, int width, int height, HWND& hWnd);
bool GenerateWindow(LPCWSTR className, LPCWSTR windowTitle, int x, int y, int width, int height, HWND& hWnd);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
Manage_Scene* obj;

bool InitializeInput();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	if(GenerateWindow(_T("Fire_Balloon"), _T("Fire_Ballon Program"), 600, 600,hWnd) && InitializeInput())
	{
		MSG msg;
		obj = new Main_Scene();
		obj->Initialize(hWnd);
	
		while(true)
		{
			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			if(msg.message == WM_QUIT) break;
			else
			{
				obj->Draw(0.0f);
			}
		}
		return msg.wParam;
	}
	return 0;
}

bool GenerateWindow(LPCWSTR className, LPCWSTR windowTitle, int width, int height, HWND& hWnd)
{
	return GenerateWindow(className, windowTitle, (GetSystemMetrics(SM_CXSCREEN)-width)/2,
		(GetSystemMetrics(SM_CYSCREEN)-height)/2, width, height, hWnd);
}

bool GenerateWindow(LPCWSTR className, LPCWSTR windowTitle, int x, int y, int width, int height, HWND& hWnd)
{
	WNDCLASSEX wcex;

	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.hInstance = GetModuleHandle(NULL);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcex.lpszClassName = className;
	wcex.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if(!RegisterClassEx(&wcex))
	{
		return false;
	}

	hWnd = CreateWindow(className, windowTitle, WS_OVERLAPPEDWINDOW, x, y, width, height,
		NULL, NULL, wcex.hInstance, NULL );

	ShowWindow(hWnd, SW_SHOWDEFAULT);

	return true;
	
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_DESTROY : 
		{
			PostQuitMessage(0);
			return 0;
		} break;
		case WM_INPUT : 
		{
			UINT dwSize;
			GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));

			LPBYTE lpb  = new BYTE[dwSize];
			if(lpb == NULL)
			{
				return 0;
			}

			GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

			RAWINPUT* raw = (RAWINPUT*)lpb;

			if(raw->header.dwType == RIM_TYPEKEYBOARD)
			{
				if(raw->data.keyboard.Message == WM_KEYDOWN || raw->data.keyboard.Message == WM_SYSKEYDOWN)
				{
					if(raw->data.keyboard.VKey ==VK_SPACE)
					{
						MessageBox(NULL, _T("Space key was pressed"), NULL, NULL);
						obj = new Manage_Scene();
						obj->Initialize(hWnd);
					}
				}
			}
		} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool InitializeInput()
{
	RAWINPUTDEVICE rawInput[1];

	rawInput[0].usUsagePage = 0x01;
	rawInput[0].usUsage = 0x06;
	rawInput[0].dwFlags = 0;
	rawInput[0].hwndTarget = 0;

	if(RegisterRawInputDevices(rawInput, 1, sizeof(rawInput[0])) == FALSE)
	{
		return false;
	}
	return true;
}

/*
void SelectScene()
{
	switch(obj->GetSceneNumber())
	{
	case obj->SCENE::TEMP_SCENE :
		obj = new Manage_Scene();
		break;
	case obj->SCENE::MAIN_SCENE :
		obj = new Main_Scene ();
		break;
	case obj->SCENE::GAME_SCENE :
		break;
	}
}
*/