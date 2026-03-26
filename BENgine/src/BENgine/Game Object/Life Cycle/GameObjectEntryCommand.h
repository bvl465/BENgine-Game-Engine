//Ben La Monica
#pragma once
#ifndef _GameObjectEntryCommand
#define _GameObjectEntryCommand
#include "../../Patterns/CommandBase.h"
#include "../GameObject.h"
class GameObject;
class GameObjectEntryCommand : public CommandBase
{
public:
	GameObjectEntryCommand() = delete;
	GameObjectEntryCommand(const GameObjectEntryCommand&) = delete;
	GameObjectEntryCommand& operator=(const GameObjectEntryCommand&) = delete;
	~GameObjectEntryCommand() = default;


	GameObjectEntryCommand(GameObject* go);

	virtual void Execute() override;

	
private:
	GameObject* gameObject;
};
#endif _GameObjectEntryCommand