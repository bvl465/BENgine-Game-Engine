#include "CollisionVisualizerAABBCommand.h"
#include "VisualizerAttorney.h"
#include "Matrix.h"
void CollisionVisualizerAABBCommand::Execute()
{

	Matrix world = Matrix(SCALE, max - min) * Matrix(TRANS, .5f * (min + max));

	VisualizerAttorney::AABBCommands::RenderAABB(world, color);
}

void CollisionVisualizerAABBCommand::Recycle()
{
	VisualizerAttorney::AABBCommands::ReturnAABBCommand(this);
}

void CollisionVisualizerAABBCommand::Initialize(const Vect& col, const Vect& cornerMin, const Vect& cornerMax)
{
	color = col;
	min = cornerMin;
	max = cornerMax;
	//world = aabbWorld;
}
