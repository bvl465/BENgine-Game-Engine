#pragma once
#ifndef _CollisionTestTerrainCommand
#define _CollisionTestTerrainCommand
#include "CollisionTestCommandBase.h"

class CollidableGroup;
class CollisionDispatchBase;
class CollisionVolumeAABB;
class CollisionTestTerrainCommand : public CollisionTestCommandBase
{
public:
	CollisionTestTerrainCommand() = delete;
	~CollisionTestTerrainCommand();
	CollisionTestTerrainCommand(const CollisionTestTerrainCommand&) = delete;
	CollisionTestTerrainCommand& operator=(const  CollisionTestTerrainCommand&) = delete;
	CollisionTestTerrainCommand(CollidableGroup* g1, CollisionDispatchBase* pd);

	virtual void Execute() override;
	CollisionVolumeAABB* pTerrainCellAABB;
private:
	CollisionDispatchBase* pDispatch;
	CollidableGroup* pG1;
	
};

#endif _CollisionTestTerrainCommand