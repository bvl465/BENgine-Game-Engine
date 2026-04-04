#include "Model.h"
#include "Matrix.h"
#include "../Math Tools/BENgineMathTools.h"
#include "CollisionVolumeAABB.h"

void CollisionVolumeAABB::ComputeData(Model& mod, const Matrix& mat)
{
	Vect* curVect = mod.getVectList();
	int numVerts = mod.getVectNum();
	Vect vect = *curVect * mat;

	float minX = vect.X();
	float minY = vect.Y();
	float minZ = vect.Z();

	float maxX = vect.X();
	float maxY = vect.Y();
	float maxZ = vect.Z();

	//Iterate through all the verts in the model to find the min and max x, y, and z values to define the AABB.
	for (int i = 1; i < numVerts; i++)
	{
		vect = curVect[i] * mat;
		if (vect.X() < minX) {
			minX = vect.X();
		}
		else if (vect.X() > maxX) {
			maxX = vect.X();
		}
		if (vect.Y() < minY) {
			minY = vect.Y();
		}
		else if (vect.Y() > maxY) {
			maxY = vect.Y();
		}
		if (vect.Z() < minZ) {
			minZ = vect.Z();
		}
		else if (vect.Z() > maxZ) {
			maxZ = vect.Z();
		}
	}
	cornerMin.set(minX, minY, minZ);
	cornerMax.set(maxX, maxY, maxZ);
	halfDiagonal = (cornerMax - cornerMin) * 0.5f;
	center = cornerMin + halfDiagonal;

	// Option 1 Multiplication
	////world = Matrix(SCALE, cornerMax - cornerMin) * Matrix(TRANS, .5f * (cornerMin + cornerMax));
	//world = Matrix(SCALE, cornerMax - cornerMin) * Matrix(TRANS, center);
	
	// Option 2 Setting
	world.set(SCALE, cornerMax - cornerMin);
	world.set(ROW_3, center);
}


bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return BENgineMathTools::AABBToBSphereIntersect(*this, other);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return BENgineMathTools::AABBToAABBIntersect(*this, other);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return BENgineMathTools::AABBToOBBIntersect(*this, other);
}


bool CollisionVolumeAABB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

void CollisionVolumeAABB::DebugView(const Vect& color) const
{
	Visualizer::ShowAABB(*this, color);
}

void CollisionVolumeAABB::SetMinMax(const Vect& min, const Vect& max)
{
	cornerMin = min;
	cornerMax = max;
	//Also have to update the half diagonal, center, and world matrix
	halfDiagonal = (cornerMax - cornerMin) * 0.5f;
	center = cornerMin + halfDiagonal;

	// Option 1 Multiplication
	////world = Matrix(SCALE, cornerMax - cornerMin) * Matrix(TRANS, .5f * (cornerMin + cornerMax));
	//world = Matrix(SCALE, cornerMax - cornerMin) * Matrix(TRANS, center);

	// Option 2 Setting
	world.set(SCALE, cornerMax - cornerMin);
	world.set(ROW_3, center);
}

float CollisionVolumeAABB::GetBSphereRadiusFromCollisionVolume() const
{
	return halfDiagonal.mag();
}

Vect CollisionVolumeAABB::GetBSphereCenterFromCollisionVolume() const
{
	return center;
}

//NOW INLINE FUNCTIONS

//const Vect& CollisionVolumeAABB::GetCornerMin() const
//{
//	return cornerMin;
//}

//const Vect& CollisionVolumeAABB::GetCornerMax() const
//{
//	return cornerMax;
//}

//const Matrix& CollisionVolumeAABB::GetWorld() const
//{
//	return world;
//}

//const Vect& CollisionVolumeAABB::GetCenter() const
//{
//	return center;
//}

//const Vect& CollisionVolumeAABB::GetHalfDiagonal() const
//{
//	return halfDiagonal;
//}
