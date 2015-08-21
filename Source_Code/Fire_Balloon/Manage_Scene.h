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
#include "User.h"

//#define BUTTON_ID 0
//#define EDITBTN_ID 100

class Manage_Scene
{
private:
	int windowWidth;
	int windowHeight;
	int sceneNumber;
	bool isGameOver;
	bool isInitialed;

public:
	Graphic_Lib *gDevice;
	enum {BUTTON_ID=10, EDITBTN_ID=100};								//나열자 둔갑술 기법(enum hack)
	enum {MAIN_SCENE=1, GAME_EXPLAIN_SCENE, GAME_SCENE, GAME_RESULT_SCENE};
	Manage_Scene();
	virtual ~Manage_Scene();
	int GetSceneNumber();
	void SetSceneNumber(int num);
	void NextScene();
	void BeforeScene();
	int GetWindowWidth();
	int GetWindowHeight();
	bool Initialized();
	void Run();
	void Update(float gameTime);
	void SetGameOver(bool state);
	bool GetGameState();
	virtual void Initialize(HWND& hWnd);
	virtual void Draw(float gameTime);
	virtual void Draw(float gameTime, User& user);
	virtual LPCWSTR GetEditWindowText();							//Main_Scene에서 EditBox의 문자열을 받기위한 함수
};

#endif