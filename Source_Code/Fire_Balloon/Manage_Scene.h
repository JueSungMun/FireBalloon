/*
	Scene�� �����ϱ� ���� �������.
	
	1. Scene���� �̵��� Scene��ȣ�� �̿��Ͽ� ����
	2. �׷��� ��ġ�� �ʱ�ȭ
	3. Draw�� �����ϵ��� �������̽� ����

	4. ���� �������̽� �����ؾ���.
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
	virtual LPCWSTR GetEditWindowText();							//Main_Scene���� EditBox�� ���ڿ��� �ޱ����� �Լ�
};

#endif