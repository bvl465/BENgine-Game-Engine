#include "VisualizerCommandPool.h"
#include "CollisionVisualizerBSphereCommand.h"
#include "CollisionVisualizerAABBCommand.h"
#include "CollisionVisualizerOBBCommand.h"

VisualizerCommandPool::VisualizerCommandPool()
{
	// Alterninatively: pre-load the recycledItems queue is a few bullets already
}

VisualizerCommandPool::~VisualizerCommandPool()
{
	// forcefully delele all recycled gameobjects
	while (!recycledBSphereCommands.empty())
	{
		delete recycledBSphereCommands.top();
		recycledBSphereCommands.pop();
	}
	while (!recycledAABBCommands.empty())
	{
		delete recycledAABBCommands.top();
		recycledAABBCommands.pop();
	}
	while (!recycledOBBCommands.empty())
	{
		delete recycledOBBCommands.top();
		recycledOBBCommands.pop();
	}
}

CollisionVisualizerBSphereCommand* VisualizerCommandPool::GetBSphereCommand()
{
	CollisionVisualizerBSphereCommand* bSphereCmd;

	if (recycledBSphereCommands.empty())
	{

		bSphereCmd = new CollisionVisualizerBSphereCommand();
	}
	else
	{

		bSphereCmd = recycledBSphereCommands.top();
		recycledBSphereCommands.pop();

	}

	return bSphereCmd;
}

CollisionVisualizerAABBCommand* VisualizerCommandPool::GetAABBCommand()
{
	CollisionVisualizerAABBCommand* aabbCmd;

	if (recycledAABBCommands.empty())
	{

		aabbCmd = new CollisionVisualizerAABBCommand();
	}
	else
	{

		aabbCmd = recycledAABBCommands.top();
		recycledAABBCommands.pop();

	}

	return aabbCmd;
}

CollisionVisualizerOBBCommand* VisualizerCommandPool::GetOBBCommand()
{
	CollisionVisualizerOBBCommand* obbCmd;

	if (recycledOBBCommands.empty())
	{

		obbCmd = new CollisionVisualizerOBBCommand();
	}
	else
	{

		obbCmd = recycledOBBCommands.top();
		recycledOBBCommands.pop();

	}

	return obbCmd;
}

void VisualizerCommandPool::ReturnBSphereCommand(CollisionVisualizerBSphereCommand* bSphereCmd)
{
	recycledBSphereCommands.push(static_cast<CollisionVisualizerBSphereCommand*>(bSphereCmd)); //NOOOOO CLUE WHY I AM CASTING IT HERE
}

void VisualizerCommandPool::ReturnAABBCommand(CollisionVisualizerAABBCommand* aabbCmd)
{
	recycledAABBCommands.push(static_cast<CollisionVisualizerAABBCommand*>(aabbCmd)); //NOOOOO CLUE WHY I AM CASTING IT HERE
}

void VisualizerCommandPool::ReturnOBBCommand(CollisionVisualizerOBBCommand* obbCmd)
{
	recycledOBBCommands.push(obbCmd);
}
