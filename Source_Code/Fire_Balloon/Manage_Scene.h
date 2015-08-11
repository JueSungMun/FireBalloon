/*
	Scene을 관리하기 위한 헤더파일.
	
	1. Scene간의 이동을 Scene번호를 이용하여 제어
	2. 그래픽 장치를 초기화
	3. Draw를 구현하도록 인터페이스 제공

	4. 음악 인터페이스 구현해야함.
*/

#ifndef MANAGE_SCENE_H
#define MANAGE_SCENE_H
#include "Graphic_Lib.h"

#define BUTTON_ID 0
#define EDITBTN_ID 100

class Manage_Scene
{
private:
	int windowWidth;
	int windowHeight;
	int sceneNumber;
	bool isInitialed;

public:
	enum SCENE {TEMP_SCENE, MAIN_SCENE, GAME_SCENE, END_SCENE};
	Graphic_Lib *gDevice;
	Manage_Scene();
	virtual ~Manage_Scene();
	int GetSceneNumber();
	void SetSceneNumber(int num);
	void NextScene();
	void BeforeScene();
	int GetWindowWidth();
	int GetWindowHeight();
	virtual void Initialize(HWND& hWnd);
	bool Initialized();
	void Run();
	void Update(float gameTime);
	virtual void Draw(float gameTime);
	virtual LPCWSTR GetEditWindowText();							//Main_Scene에서 EditBox의 문자열을 받기위한 함수
};

#endif