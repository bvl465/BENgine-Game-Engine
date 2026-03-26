#pragma once
#ifndef _CollisionTestPairCommand
#define _CollisionTestPairCommand

#include "CollisionTestCommandBase.h"
class CollidableGroup;
class CollisionVolumeAABB;
class CollisionDispatchBase;

class CollisionTestPairCommand : public CollisionTestCommandBase
{
public:
	CollisionTestPairCommand() = delete;
	~CollisionTestPairCommand();
	CollisionTestPairCommand(const CollisionTestPairCommand&) = delete;
	CollisionTestPairCommand& operator=(const  CollisionTestPairCommand&) = delete;
	CollisionTestPairCommand(CollidableGroup* g1, CollidableGroup* g2, CollisionDispatchBase* pd);
	virtual void Execute() override;

private:
	CollisionDispatchBase* pDispatch;
	CollidableGroup* pG1;
	CollidableGroup* pG2;

	//CollisionVolumeAABB* pG1AABB;
	//CollisionVolumeAABB* pG2AABB;

};

#endif _CollisionTestPairCommand