//Ben La Monica
#pragma once
#ifndef _CollisionVisualizerAABBCommand
#define _CollisionVisualizerAABBCommand

#include "VisualizerCommandBase.h"
#include "Vect.h"
class CollisionVisualizerAABBCommand : public VisualizerCommandBase
{
public:
	CollisionVisualizerAABBCommand() = default;
	CollisionVisualizerAABBCommand(const CollisionVisualizerAABBCommand&) = delete;
	CollisionVisualizerAABBCommand& operator=(const CollisionVisualizerAABBCommand&) = delete;
	~CollisionVisualizerAABBCommand() = default;

	virtual void Execute() override;
	virtual void Recycle() override;
	void Initialize(const Vect& col, const Vect& cornerMin, const Vect& cornerMax);

private:
	Vect min = Vect(0.f, 0.f, 0.f);
	Vect max = Vect(0.f, 0.f, 0.f);
	Vect color = Vect(0.f, 0.f, 0.f);
};
#endif _CollisionVisualizerAABBCommand