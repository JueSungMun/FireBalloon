#include "All_Header.h"

ObjectManager::ObjectManager(void) : stageNum(1), MAXIMUM_ENEMY(0)
{
	//for(int i=0; i<MAX_ENEMY; i++)
		//isAlive[i] = FALSE;
	Initialize();
}

ObjectManager::ObjectManager(int stage) : stageNum(stage)
{
	Initialize();
}

ObjectManager::~ObjectManager(void)
{
}

void ObjectManager::setAlive(int idx, BOOL isalive)
{
	isAlive[idx] = isalive;
	this->getEnemy(idx).setVisible(isalive);
}

void ObjectManager::insertObj()
{
	//for(int i=0; i<MAX_ENEMY; i++)
	for(int i=0; i<ManageMaxEnemy(); i++)
	{
		if(!isAlive[i])
		{
			RECT rct;
			rct.left = BIRD_RECT_LEFT; 
			rct.top = BIRD_RECT_TOP; 
			rct.right = BIRD_RECT_RIGHT; 
			rct.bottom = BIRD_RECT_BOTTOM;
			v1.push_back(Enemy(i));
			isAlive[i]=TRUE;
			this->getEnemy(i).initEnemy(rct);
			break;
		}
	}
}

BOOL ObjectManager::getAlive(int idx)
{
	return isAlive[idx];
}

void ObjectManager::deleteObj(int id)
{
	for(iter= v1.begin(); iter != v1.end();)
		{
			if( id == iter->getID())
			{
				setAlive(id, FALSE);
				
				v1.erase(iter++);
				break;
			}
			else
				iter++;
		}
}

Enemy& ObjectManager::getEnemy(int id)
{
	for(iter= v1.begin(); iter != v1.end();)
	{
		if( id == iter->getID())
		{
			return *iter;
		}
		else
			iter++;
	}
	//return NULL;
}

std::list<Enemy>& ObjectManager::getEnemyList()
{
	return v1;
}

void ObjectManager::IncreaseStageNumber()
{
	stageNum++;
}

int ObjectManager::ManageMaxEnemy()
{
	switch (stageNum)
	{
	case 1:
		return ObjectManager::ENEMY::STAGE1;
		break;
	case 2:
		return ObjectManager::ENEMY::STAGE2;
		break;
	case 3:
		return ObjectManager::ENEMY::STAGE3;
		break;
	case 4:
		return ObjectManager::ENEMY::STAGE4;
		break;
	case 5:
		return ObjectManager::ENEMY::STAGE5;
		break;
	}
	return 0;
}

bool ObjectManager::Initialize()
{
	MAXIMUM_ENEMY = ManageMaxEnemy();
	isAlive = new BOOL[MAXIMUM_ENEMY];
	for(int i=0; i<MAXIMUM_ENEMY; i++)
		isAlive[i] = FALSE;
	return true;
}


int ObjectManager::GetStageNumber()
{
	return stageNum;
}


int ObjectManager::GetMaxEnemyNumber()
{
	return MAXIMUM_ENEMY;
}