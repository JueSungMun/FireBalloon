#include "All_Header.h"


ObjectManager::ObjectManager(void)
{
}

ObjectManager::~ObjectManager(void)
{
}

void ObjectManager::insertObj(int id)
{
	v1.push_back(Enemy(id));
}

void ObjectManager::deleteObj(int id)
{
	for(iter= v1.begin(); iter != v1.end();)
		{
			if( id == iter->getID())
			{
				v1.erase(iter++);
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
		}/*
	return NULL;*/
}

std::list<Enemy> ObjectManager::getEnemyList()
{
	return v1;
}