#pragma once
#include "All_Header.h"

class ObjectManager
{
private:
	std::list<Enemy> v1;
	std::list<Enemy>::iterator iter;
	int size;
	BOOL isAlive[MAX_ENEMY];

public:
	ObjectManager(void);
	~ObjectManager(void);
	void insertObj();
	void deleteObj(int);
	void setAlive(int, BOOL);
	BOOL getAlive(int);
	Enemy& getEnemy(int); //id�� �ش��ϴ� ���� ��ȣ�� ã�Ƽ� ��ȯ
	std::list<Enemy> getEnemyList(); 
};

