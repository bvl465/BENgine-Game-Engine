#pragma once
#ifndef _EnemyPool
#define _EnemyPool
#include <list>
#include <stack>
class Enemy;

class EnemyPool
{
private:
	std::stack<Enemy*> recycledEnemys;
	std::list<Enemy*> activeEnemys;
public:
	EnemyPool();
	EnemyPool(const EnemyPool&) = delete;
	EnemyPool& operator=(const EnemyPool&) = delete;
	~EnemyPool();

	Enemy* GetEnemy();

	void ReturnEnemy(Enemy* bullet);
};


#endif _EnemyPool
