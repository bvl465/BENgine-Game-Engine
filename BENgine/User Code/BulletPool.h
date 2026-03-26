#pragma once
#ifndef _BulletPool
#define _BulletPool
#include <list>
#include <stack>
class Bullet;

class BulletPool
{
private:
	std::stack<Bullet*> recycledBullets;
	std::list<Bullet*> activeBullets;
public:
	BulletPool();
	BulletPool(const BulletPool&) = delete;
	BulletPool& operator=(const BulletPool&) = delete;
	~BulletPool();

	Bullet* GetBullet();

	void ReturnBullet(Bullet* bullet);
};


#endif _BulletPool
