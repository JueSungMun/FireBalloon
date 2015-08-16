#pragma once

class ObjectManager
{
private:
	std::list<Enemy> v1;
	std::list<Enemy>::iterator iter;
	int size;

public:
	ObjectManager(void);
	~ObjectManager(void);
	void insertObj(int);
	void deleteObj(int);
	Enemy& getEnemy(int); //id에 해당하는 적의 번호를 찾아서 반환
	std::list<Enemy> getEnemyList(); 
};

