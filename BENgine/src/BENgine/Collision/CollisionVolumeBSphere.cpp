#include "Model.h"
#include "Matrix.h"
#include "../Math Tools/BENgineMathTools.h"
#include "CollisionVolumeBSphere.h"

void CollisionVolumeBSphere::DebugView(const Vect& color) const
{
	Visualizer::ShowBSphere(*this, color);
}

void CollisionVolumeBSphere::ComputeData(Model& mod, const Matrix& mat)
{
	center = mod.getCenter() * mat;

	radius = mod.getRadius() * mat.get(MatrixRowType::ROW_0).mag(); //assumes uniform scaling
}


bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return BENgineMathTools::AABBToBSphereIntersect(other, *this);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return BENgineMathTools::BSphereToOBBIntersect(*this, other);
}

bool CollisionVolumeBSphere::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

float CollisionVolumeBSphere::GetBSphereRadiusFromCollisionVolume() const
{
	return radius;
}

Vect CollisionVolumeBSphere::GetBSphereCenterFromCollisionVolume() const
{
	return center;
}

void CollisionVolumeBSphere::SetCenterAndRadius(const Vect& c, float r)
{
	center = c;
	radius = r;
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return BENgineMathTools::BSphereToBSphereIntersect(*this, other);
}

//NOW INLINE FUNCTIONS

//const Vect& CollisionVolumeBSphere::GetCenter() const
//{
//	return center;
//}

//float CollisionVolumeBSphere::GetRadius() const
//{
//	return radius;
//}

//float CollisionVolumeBSphere::GetRadiusSquared() const
//{
//	return radius * radius;
//}