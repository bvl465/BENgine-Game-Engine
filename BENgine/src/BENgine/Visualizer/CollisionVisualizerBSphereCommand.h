//Ben La Monica
#pragma once
#ifndef _CollisionVisualizerBSphereCommand
#define _CollisionVisualizerBSphereCommand

#include "VisualizerCommandBase.h"
#include "Vect.h"
class CollisionVisualizerBSphereCommand : public VisualizerCommandBase
{
public:
	CollisionVisualizerBSphereCommand() = default;
	CollisionVisualizerBSphereCommand(const CollisionVisualizerBSphereCommand&) = delete;
	CollisionVisualizerBSphereCommand& operator=(const CollisionVisualizerBSphereCommand&) = delete;
	~CollisionVisualizerBSphereCommand() = default;

	virtual void Execute() override;
	virtual void Recycle() override;
	void Initialize(const Vect& col, const Vect& cent, float rad);

private:
	Vect center = Vect(0.f, 0.f, 0.f);
	Vect color = Vect(0.f, 0.f, 0.f);
	float radius = 0.f;
};
#endif _CollisionVisualizerBSphereCommand