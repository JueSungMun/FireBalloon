#include "All_Header.h"

ObjectManager::ObjectManager(void)
{
	for(int i=0; i<MAX_ENEMY; i++)
		isAlive[i] = FALSE;
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
	for(int i=0; i<MAX_ENEMY; i++)
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

std::list<Enemy> ObjectManager::getEnemyList()
{
	return v1;
}