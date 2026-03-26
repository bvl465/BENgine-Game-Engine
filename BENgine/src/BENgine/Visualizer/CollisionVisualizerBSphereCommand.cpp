#include "CollisionVisualizerBSphereCommand.h"
#include "VisualizerAttorney.h"
#include "Matrix.h"
void CollisionVisualizerBSphereCommand::Execute()
{

	//computes the world matrix based on the center and radius of the sphere
	Matrix worldBS = Matrix(SCALE, Vect(radius, radius, radius)) * Matrix(TRANS, center);
	VisualizerAttorney::Commands::RenderBSphere(worldBS, color);
}

void CollisionVisualizerBSphereCommand::Recycle()
{
	VisualizerAttorney::Commands::ReturnBSphereCommand(this);
}



void CollisionVisualizerBSphereCommand::Initialize(const Vect& col, const Vect& cent, float rad)
{
	color = col;
	center = cent;
	radius = rad;
}
