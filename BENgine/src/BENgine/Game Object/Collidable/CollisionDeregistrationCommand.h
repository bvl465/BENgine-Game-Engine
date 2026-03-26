//Ben La Monica
#pragma once
#ifndef _CollisionDeregistrationCommand
#define _CollisionDeregistrationCommand
#include "../../Patterns/CommandBase.h"
class Collidable;
class CollisionDeregistrationCommand : public CommandBase
{
public:
	CollisionDeregistrationCommand() = delete;
	CollisionDeregistrationCommand(const CollisionDeregistrationCommand&) = delete;
	CollisionDeregistrationCommand& operator=(const CollisionDeregistrationCommand&) = delete;
	~CollisionDeregistrationCommand() = default;


	CollisionDeregistrationCommand(Collidable* co);

	virtual void Execute() override;


private:
	Collidable* collidable;
};
#endif _CollisionDeregistrationCommand