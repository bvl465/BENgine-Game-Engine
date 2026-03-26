#pragma once
#ifndef _CollisionTestCommandBase
#define _CollisionTestCommandBase

class CollisionTestCommandBase
{
public:
	CollisionTestCommandBase() {};
	virtual ~CollisionTestCommandBase() {};
	CollisionTestCommandBase(const CollisionTestCommandBase&) = delete;
	CollisionTestCommandBase& operator=(const  CollisionTestCommandBase&) = delete;

	virtual void Execute() = 0;
};

#endif _CollisionTestCommandBase