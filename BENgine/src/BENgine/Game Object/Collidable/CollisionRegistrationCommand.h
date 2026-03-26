//Ben La Monica
#pragma once
#ifndef _CollisionRegistrationCommand
#define _CollisionRegistrationCommand
#include "../../Patterns/CommandBase.h"
class Collidable;
class CollisionRegistrationCommand : public CommandBase
{
public:
	CollisionRegistrationCommand() = delete;
	CollisionRegistrationCommand(const CollisionRegistrationCommand&) = delete;
	CollisionRegistrationCommand& operator=(const CollisionRegistrationCommand&) = delete;
	~CollisionRegistrationCommand() = default;


	CollisionRegistrationCommand(Collidable* co);

	virtual void Execute() override;


private:
	Collidable* collidable;
};
#endif _CollisionRegistrationCommand