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
	enum {BUTTON_ID=10, EDITBTN_ID=100};								//������ �а��� ���(enum hack)
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
	virtual LPCWSTR GetEditWindowText();							//Main_Scene���� EditBox�� ���ڿ��� �ޱ����� �Լ�
};

#endif