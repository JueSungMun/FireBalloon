#include <Windows.h>
#include "Main_Scene.h"
#include "GameExplainScene.h"
#include "GameScene.h"
#include "User.h"
#include "GameResultScene.h"

bool GenerateWindow(LPCWSTR className, LPCWSTR windowTitle, int width, int height, HWND& hWnd);
bool GenerateWindow(LPCWSTR className, LPCWSTR windowTitle, int x, int y, int width, int height, HWND& hWnd);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
WNDCLASSEX wcex;
Manage_Scene* obj;
User* user;
bool InitializeInput();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;

	if(GenerateWindow(_T("Fire_Balloon"), _T("Fire_Ballon Program"), 600, 700, hWnd) && InitializeInput())
	{
		MSG msg;
		obj = new Main_Scene();
		obj->Initialize(hWnd);
		obj->Draw(0.0f);
		
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
				if(obj->GetSceneNumber() == obj->GAME_SCENE)
				{
					obj->Draw(0.0f, *user);
				}
				
				if (obj->GetGameState() && obj->GetSceneNumber() == obj->GAME_SCENE)
				{
					delete obj;
					obj = new GameResultScene();
					obj->Initialize(hWnd);
					obj->Draw(0.0f, *user);
				}
			}
		}
		return msg.wParam;
	}
	UnregisterClass(_T("Fire_Balloon"), wcex.hInstance);
	delete obj;
	delete user;
	return 0;
}

bool GenerateWindow(LPCWSTR className, LPCWSTR windowTitle, int width, int height, HWND& hWnd)
{
	return GenerateWindow(className, windowTitle, (GetSystemMetrics(SM_CXSCREEN)-width)/2,
		(GetSystemMetrics(SM_CYSCREEN)-height)/2, width, height, hWnd);
}

bool GenerateWindow(LPCWSTR className, LPCWSTR windowTitle, int x, int y, int width, int height, HWND& hWnd)
{
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
	HDC hdc;
	PAINTSTRUCT ps;

	switch(message)
	{
		case WM_CREATE:
			return 0;
			break;
		case WM_DESTROY : 
			PostQuitMessage(0);
			return 0;
			break;
		case WM_PAINT :
			hdc = BeginPaint(hWnd, &ps);
			obj->Draw(0.0f);
			EndPaint(hWnd, &ps);
			return 0;
			break;
		case WM_LBUTTONDOWN : 
			if(obj->GetSceneNumber() == obj->GAME_EXPLAIN_SCENE)
			{
				delete obj;
				obj = new GameScene();
				obj->Initialize(hWnd);
				obj->Draw(0.0f, *user);
			}
			else if(obj->GetSceneNumber() == obj->GAME_RESULT_SCENE)
			{
				delete obj;
				obj = new Main_Scene();
				obj->Initialize(hWnd);
				obj->Draw(0.0f);
			}
			return 0;
			break;
		case WM_COMMAND : 
			switch(LOWORD(wParam))
			{
			case obj->BUTTON_ID:
				if(!_tcscmp(obj->GetEditWindowText(),_T("")))
					MessageBox(hWnd, _T("닉네임을 입력해주세요"), _T("Button"), MB_OK);
				else
				{
					user = new User(obj->GetEditWindowText());
					delete obj;
					obj = new GameExplainScene();
					obj->Initialize(hWnd);
					obj->Draw(0.0f);
				}
				break;
			}
			break;
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
					if(raw->data.keyboard.VKey ==VK_SPACE || raw->data.keyboard.VKey == VK_RETURN)
					{
						if(obj->GetSceneNumber() == obj->GAME_RESULT_SCENE)
						{
							delete obj;
							obj = new Main_Scene();
							obj->Initialize(hWnd);
							obj->Draw(0.0f);
						}
						//wchar_t sceneNum[10];
						//_itow_s(obj->GetSceneNumber(), sceneNum, 10);
						//MessageBox(NULL, sceneNum, NULL, NULL);
						//delete obj;
						//obj = new Manage_Scene();
						//obj->Initialize(hWnd);
						//obj->Draw(0.0f);
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