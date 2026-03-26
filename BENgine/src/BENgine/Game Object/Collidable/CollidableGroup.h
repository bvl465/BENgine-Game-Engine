//Ben La Monica
#pragma once
#ifndef _CollidableGroup
#define _CollidableGroup
#include <list>
class Collidable;
class CollisionVolumeAABB;
class CollidableGroup
{
public:

	using CollidableCollection = std::list<Collidable*>;
	using StorageEntryRef = CollidableCollection::iterator;
	CollidableGroup();
	CollidableGroup(const CollidableGroup&) = delete;
	CollidableGroup& operator=(const CollidableGroup&) = delete;
	~CollidableGroup();


	const CollidableCollection& GetColliderCollection();
	void Register(Collidable* co); //add to CollideCol
	void Deregister(Collidable* co); //remove from storageList
	void UpdateGroupAABB();
	CollisionVolumeAABB& GetGroupAABB() const;
private:
	CollidableCollection CollideCol;
	CollisionVolumeAABB* const groupAABB;
};
#endif _CollidableGroup