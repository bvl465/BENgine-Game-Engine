#pragma once
#ifndef _CollisionTestSelfCommand
#define _CollisionTestSelfCommand
#include "CollisionTestCommandBase.h"

class CollidableGroup;
class CollisionDispatchBase;

class CollisionTestSelfCommand : public CollisionTestCommandBase
{
public:
	CollisionTestSelfCommand() = delete;
	~CollisionTestSelfCommand();
	CollisionTestSelfCommand(const CollisionTestSelfCommand&) = delete;
	CollisionTestSelfCommand& operator=(const  CollisionTestSelfCommand&) = delete;
	CollisionTestSelfCommand(CollidableGroup* g1, CollisionDispatchBase* pd);

	virtual void Execute() override;

private:
	CollisionDispatchBase* pDispatch;

	CollidableGroup* pG1;
};

#endif _CollisionTestSelfCommand