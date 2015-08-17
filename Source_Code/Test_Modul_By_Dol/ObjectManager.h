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
	Enemy& getEnemy(int); //id에 해당하는 적의 번호를 찾아서 반환
	std::list<Enemy> getEnemyList(); 
};

