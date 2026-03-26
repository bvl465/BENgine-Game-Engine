#include "EnemyPool.h"
#include "Enemy.h"

EnemyPool::EnemyPool()
{
	// Alterninatively: pre-load the recycledItems queue is a few bullets already
}

EnemyPool::~EnemyPool()
{
	// forcefully delete all recycled gameobjects
	while (!recycledEnemys.empty())
	{
		delete recycledEnemys.top();
		recycledEnemys.pop();
	}

	for (auto it = activeEnemys.begin(); it != activeEnemys.end(); ++it) {
		delete* it;
	}
	activeEnemys.clear();
}

Enemy* EnemyPool::GetEnemy()
{
	Enemy* bullet;

	if (recycledEnemys.empty())
	{
		bullet = new Enemy();
	}
	else
	{

		bullet = recycledEnemys.top();
		recycledEnemys.pop();

	}
	activeEnemys.push_back(bullet);
	return bullet;
}

void EnemyPool::ReturnEnemy(Enemy* bullet)
{
	recycledEnemys.push(bullet);
	activeEnemys.remove(bullet);
}