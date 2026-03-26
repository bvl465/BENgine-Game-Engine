#include "CollisionVisualizerOBBCommand.h"
#include "VisualizerAttorney.h"
void CollisionVisualizerOBBCommand::Execute()
{
	Matrix renderMatrix = Matrix(SCALE, max - min) * Matrix(TRANS, .5f * (min + max)) * world;

	VisualizerAttorney::OBBCommands::RenderOBB(renderMatrix, color);
}

void CollisionVisualizerOBBCommand::Recycle()
{
	VisualizerAttorney::OBBCommands::ReturnOBBCommand(this);
}

void CollisionVisualizerOBBCommand::Initialize(const Matrix& obbWorld, const Vect& col, const Vect& cornerMin, const Vect& cornerMax)
{
	world = obbWorld;
	min = cornerMin;
	max = cornerMax;
	color = col;
}