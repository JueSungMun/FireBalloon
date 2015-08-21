#pragma once

class ObjectManager
{
private:
	std::list<Enemy> v1;
	std::list<Enemy>::iterator iter;
	int stageNum;
	enum ENEMY {STAGE1 = 3, STAGE2 = 6, STAGE3 = 9, STAGE4 = 12, STAGE5 = 15};
	//BOOL isAlive[MAX_ENEMY];
	BOOL* isAlive;//[MAX_ENEMY];
	int MAXIMUM_ENEMY;
public:
	ObjectManager(void);
	~ObjectManager(void);
	ObjectManager(int);
	void insertObj();
	void deleteObj(int);
	void setAlive(int, BOOL);
	BOOL getAlive(int);
	Enemy& getEnemy(int); //id�� �ش��ϴ� ���� ��ȣ�� ã�Ƽ� ��ȯ
	std::list<Enemy>& getEnemyList(); 
	void IncreaseStageNumber();
	int ManageMaxEnemy();
	bool Initialize();
	int GetStageNumber();
	int GetMaxEnemyNumber();
};


