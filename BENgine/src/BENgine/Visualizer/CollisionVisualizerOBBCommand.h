//Ben La Monica
#pragma once
#ifndef _CollisionVisualizerOBBCommand
#define _CollisionVisualizerOBBCommand

#include "VisualizerCommandBase.h"
#include "Vect.h"
#include "Matrix.h"
class CollisionVisualizerOBBCommand : public VisualizerCommandBase
{
public:
	CollisionVisualizerOBBCommand() = default;
	CollisionVisualizerOBBCommand(const CollisionVisualizerOBBCommand&) = delete;
	CollisionVisualizerOBBCommand& operator=(const CollisionVisualizerOBBCommand&) = delete;
	~CollisionVisualizerOBBCommand() = default;

	virtual void Execute() override;
	virtual void Recycle() override;
	void Initialize(const Matrix& obbWorld, const Vect& col, const Vect& cornerMin, const Vect& cornerMax);

private:
	Matrix world = Matrix(IDENTITY);
	Vect min = Vect(0.f, 0.f, 0.f);
	Vect max = Vect(0.f, 0.f, 0.f);
	Vect color = Vect(0.f, 0.f, 0.f);
};
#endif _CollisionVisualizerOBBCommand