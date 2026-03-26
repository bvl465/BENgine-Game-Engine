#pragma once
#ifndef _VisualizerCommandPool
#define _VisualizerCommandPool

#include <stack>
class CollisionVisualizerBSphereCommand;
class CollisionVisualizerAABBCommand;
class CollisionVisualizerOBBCommand;

class VisualizerCommandPool
{
private:
	std::stack<CollisionVisualizerBSphereCommand*> recycledBSphereCommands;
	std::stack<CollisionVisualizerAABBCommand*> recycledAABBCommands;
	std::stack<CollisionVisualizerOBBCommand*> recycledOBBCommands;

public:
	VisualizerCommandPool();
	VisualizerCommandPool(const VisualizerCommandPool&) = delete;
	VisualizerCommandPool& operator=(const VisualizerCommandPool&) = delete;
	~VisualizerCommandPool();

	CollisionVisualizerBSphereCommand* GetBSphereCommand();
	CollisionVisualizerAABBCommand* GetAABBCommand();
	CollisionVisualizerOBBCommand* GetOBBCommand();


	void ReturnBSphereCommand(CollisionVisualizerBSphereCommand* bSphereCmd);
	void ReturnAABBCommand(CollisionVisualizerAABBCommand* aabbCmd);
	void ReturnOBBCommand(CollisionVisualizerOBBCommand* obbCmd);
};


#endif _VisualizerCommandPool
