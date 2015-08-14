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
	Enemy& getEnemy(int); //id�� �ش��ϴ� ���� ��ȣ�� ã�Ƽ� ��ȯ
	std::list<Enemy> getEnemyList(); 
};

