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

class Manage_Scene
{
private:
	int sceneNumber;
	bool isInitialed;

public:
	enum SCENE {TEMP_SCENE, MAIN_SCENE, GAME_SCENE, END_SCENE};
	Graphic_Lib *gDevice;
	Manage_Scene();
	~Manage_Scene();
	int GetSceneNumber();
	void SetSceneNumber(int num);
	void NextScene();
	void BeforeScene();
	//virtual void Draw() = 0;

	virtual void Initialize(HWND& hWnd);
	bool Initialized();
	void Run();
	void Update(float gameTime);
	virtual void Draw(float gameTime);
};

#endif