#include "Model.h"
#include "Matrix.h"
#include "../Math Tools/BENgineMathTools.h"
#include "CollisionVolumeOBB.h"




void CollisionVolumeOBB::ComputeData(Model& mod, const Matrix& mat)
{

	mod; //to prevent the unreferenced formal parameter warning that is treated as an error

	world = mat;

	scaleFactorSquared = world.get(ROW_0).magSqr();
	
	center = (cornerMin + halfDiagonal) * world;

}


bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return BENgineMathTools::BSphereToOBBIntersect(other, *this);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeAABB& other) const
{

	return BENgineMathTools::AABBToOBBIntersect(other, *this);
	//return BENgineMathTools::AABBToOBBIntersect(other, *this);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeOBB& other) const
{
	//other;
	//return false;
	return BENgineMathTools::OBBToOBBIntersect(*this, other);;
}


bool CollisionVolumeOBB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

void CollisionVolumeOBB::InitializeOBBWithModel(const Model& mod)
{
	cornerMin = mod.getMinAABB();
	cornerMax = mod.getMaxAABB();
	halfDiagonal = (cornerMax - cornerMin) * 0.5f;

}

void CollisionVolumeOBB::DebugView(const Vect& color) const
{
	Visualizer::ShowOBB(*this, color);
}

float CollisionVolumeOBB::GetBSphereRadiusFromCollisionVolume() const
{
	return (world.get(ROW_0).mag() * halfDiagonal).mag();
	//.mag() is very expensive
}

Vect CollisionVolumeOBB::GetBSphereCenterFromCollisionVolume() const
{
	return center;
}

//NOW INLINE FUNCTIONS

//const Vect& CollisionVolumeOBB::GetCornerMin() const
//{
//	return cornerMin;
//}

//const Vect& CollisionVolumeOBB::GetCornerMax() const
//{
//	return cornerMax;
//}

//const Matrix& CollisionVolumeOBB::GetWorld() const
//{
//	return world;
//}

//const Vect& CollisionVolumeOBB::GetCenter() const
//{
//	return center;
//}

//const Vect& CollisionVolumeOBB::GetHalfDiagonal() const
//{
//	return halfDiagonal;
//}

//const float CollisionVolumeOBB::GetScaleFactorSquared() const
//{
//	return scaleFactorSquared;
//}
