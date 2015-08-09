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