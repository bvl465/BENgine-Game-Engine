//Ben La Monica
#pragma once
#ifndef _GameObjectExitCommand
#define _GameObjectExitCommand
#include "../../Patterns/CommandBase.h"
#include "../GameObject.h"
class GameObject;
class GameObjectExitCommand : public CommandBase
{
public:
	GameObjectExitCommand() = delete;
	GameObjectExitCommand(const GameObjectExitCommand&) = delete;
	GameObjectExitCommand& operator=(const GameObjectExitCommand&) = delete;
	~GameObjectExitCommand() = default;


	GameObjectExitCommand(GameObject* dr);

	virtual void Execute() override;


private:
	GameObject* gameObject;
};
#endif _GameObjectExitCommand