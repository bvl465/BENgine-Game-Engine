#include "BulletPool.h"
#include "Bullet.h"

BulletPool::BulletPool()
{
	// Alterninatively: pre-load the recycledItems queue is a few bullets already
}

BulletPool::~BulletPool()
{
	// forcefully delete all recycled gameobjects
	while (!recycledBullets.empty())
	{
		delete recycledBullets.top();
		recycledBullets.pop();
	}
	
	for (auto it = activeBullets.begin(); it != activeBullets.end(); ++it) {
		delete *it;
	}
	activeBullets.clear();
}

Bullet* BulletPool::GetBullet()
{
	Bullet* bullet;

	if (recycledBullets.empty())
	{
		bullet = new Bullet();
	}
	else
	{

		bullet = recycledBullets.top();
		recycledBullets.pop();

	}
	activeBullets.push_back(bullet);
	return bullet;
}

void BulletPool::ReturnBullet(Bullet* bullet)
{
	recycledBullets.push(bullet);
	activeBullets.remove(bullet);
}