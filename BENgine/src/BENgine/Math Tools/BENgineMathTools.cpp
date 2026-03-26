#include "BENgineMathTools.h"

#include "Vect.h"

#include "../Collision/CollisionVolumeBSphere.h"
#include "../Collision/CollisionVolumeAABB.h"
#include "../Collision/CollisionVolumeOBB.h"

bool BENgineMathTools::Intersect(const CollisionVolume& cv1, const CollisionVolume& cv2)
{
    return cv1.IntersectAccept(cv2);
}

bool BENgineMathTools::BSphereToBSphereIntersect(const CollisionVolumeBSphere& bs1, const CollisionVolumeBSphere& bs2)
{
	float radiusSum = bs1.GetRadius() + bs2.GetRadius();
	return (bs1.GetCenter() - bs2.GetCenter()).magSqr() < (radiusSum * radiusSum);
}

bool BENgineMathTools::BSphereToPointIntersect(const CollisionVolumeBSphere& bs, const Vect& point)
{
    //return ((bs.GetCenter() - point).magSqr() < (bs.GetRadius() * bs.GetRadius()));
    return ((bs.GetCenter() - point).magSqr() < (bs.GetRadiusSquared()));
}

bool BENgineMathTools::BSphereToOBBIntersect(const CollisionVolumeBSphere& bs, const CollisionVolumeOBB& obb)
{

    Vect bsCenterLocal = (bs.GetCenter()) * (obb.GetWorld().getInv());
    if (OBBToPointIntersect(obb, bsCenterLocal)) {
        return true;
    }
    else {
        Vect v = VectClamp(bsCenterLocal, obb.GetCornerMin(), obb.GetCornerMax());
        //return ((bsCenterLocal - v).magSqr() < (bs.GetRadius() * bs.GetRadius()));
        return ((bsCenterLocal - v).magSqr() < (bs.GetRadiusSquared()));
    }

}


Vect BENgineMathTools::VectClamp(const Vect v, const Vect min, const Vect max)
{
    Vect clamped = v;
    if (v.X() < min.X())
    {
        clamped.X() = min.X();
    }
    else if (v.X() > max.X())
    {
        clamped.X() = max.X();
    }
    if (v.Y() < min.Y())
    {
        clamped.Y() = min.Y();
    }
    else if (v.Y() > max.Y())
    {
        clamped.Y() = max.Y();
    }
    if (v.Z() < min.Z())
    {
        clamped.Z() = min.Z();
    }
    else if (v.Z() > max.Z())
    {
        clamped.Z() = max.Z();
    }
    return clamped;
}

float BENgineMathTools::FloatClamp(const float val, const float min, const float max)
{
	if (val < min)
	{
		return min;
	}
	else if (val > max)
	{
		return max;
	}
	return val;
}

int BENgineMathTools::IntClamp(const int val, const int min, const int max)
{
	if (val < min)
	{
		return min;
	}
	else if (val > max)
	{
		return max;
	}
	return val;
}

bool BENgineMathTools::Overlap(const float min1, const float max1, const float min2, const float max2)
{
	return (!((max1 < min2) || (max2 < min1)));
}

bool BENgineMathTools::AABBToBSphereIntersect(const CollisionVolumeAABB& aabb, const CollisionVolumeBSphere& bs)
{
	if (AABBToPointIntersect(aabb, bs.GetCenter()))
	{
		return true;
	}
	else {
		Vect v = VectClamp(bs.GetCenter(), aabb.GetCornerMin(), aabb.GetCornerMax());
		return BSphereToPointIntersect(bs, v);
	}
}

bool BENgineMathTools::AABBToAABBIntersect(const CollisionVolumeAABB& aabb1, const CollisionVolumeAABB& aabb2)
{
	return (Overlap(aabb1.GetCornerMin().X(), aabb1.GetCornerMax().X(), aabb2.GetCornerMin().X(), aabb2.GetCornerMax().X()) &&
		    Overlap(aabb1.GetCornerMin().Y(), aabb1.GetCornerMax().Y(), aabb2.GetCornerMin().Y(), aabb2.GetCornerMax().Y()) &&
		    Overlap(aabb1.GetCornerMin().Z(), aabb1.GetCornerMax().Z(), aabb2.GetCornerMin().Z(), aabb2.GetCornerMax().Z()));
}

bool BENgineMathTools::AABBToPointIntersect(const CollisionVolumeAABB& aabb, const Vect& point)
{
    return ((aabb.GetCornerMax().X() >= point.X()) && (point.X() >= aabb.GetCornerMin().X()) &&
            (aabb.GetCornerMax().Y() >= point.Y()) && (point.Y() >= aabb.GetCornerMin().Y()) &&
            (aabb.GetCornerMax().Z() >= point.Z()) && (point.Z() >= aabb.GetCornerMin().Z()));
}

bool BENgineMathTools::AABBToOBBIntersect(const CollisionVolumeAABB& aabb, const CollisionVolumeOBB& obb)
{
	//I use a bunch of if statements instead of a for loop to avoid having to compute the cross products unnecissarily
	//and to avoid storing variables when its not necessary.

	Vect axis;
	//Check the axes of the second OBB
	Matrix mat1 = obb.GetWorld();
	axis = mat1.get(ROW_0);
	if (axis.isZero() == false && AABBWithOBBAxisOverlap(aabb, obb, axis) == false) {
		return false;
	}
	axis = mat1.get(ROW_1);
	if (axis.isZero() == false && AABBWithOBBAxisOverlap(aabb, obb, axis) == false) {
		return false;
	}
	axis = mat1.get(ROW_2);
	if (axis.isZero() == false && AABBWithOBBAxisOverlap(aabb, obb, axis) == false) {
		return false;
	}

	//Check the axes of the first OBB
	mat1 = aabb.GetWorld();
	axis = mat1.get(ROW_0);
	if (axis.isZero() == false && AABBWithOBBAxisOverlap(aabb, obb, axis) == false) {
		return false;
	}

	axis = mat1.get(ROW_1);

	if (axis.isZero() == false && AABBWithOBBAxisOverlap(aabb, obb, axis) == false) {
		return false;
	}

	axis = mat1.get(ROW_2);

	if (axis.isZero() == false && AABBWithOBBAxisOverlap(aabb, obb, axis) == false) {
		return false;
	}

	//Check the cross products of the axes
	const Matrix mat2 = obb.GetWorld();
	axis = mat1.get(ROW_0).cross(mat2.get(ROW_0));
	if (axis.isZero() == false && AABBWithOBBAxisOverlap(aabb, obb, axis) == false) {
		return false;
	}
	axis = mat1.get(ROW_0).cross(mat2.get(ROW_1));
	if (axis.isZero() == false && AABBWithOBBAxisOverlap(aabb, obb, axis) == false) {
		return false;
	}
	axis = mat1.get(ROW_0).cross(mat2.get(ROW_2));
	if (axis.isZero() == false && AABBWithOBBAxisOverlap(aabb, obb, axis) == false) {
		return false;
	}
	axis = mat1.get(ROW_1).cross(mat2.get(ROW_0));
	if (axis.isZero() == false && AABBWithOBBAxisOverlap(aabb, obb, axis) == false) {
		return false;
	}
	axis = mat1.get(ROW_1).cross(mat2.get(ROW_1));
	if (axis.isZero() == false && AABBWithOBBAxisOverlap(aabb, obb, axis) == false) {
		return false;
	}
	axis = mat1.get(ROW_1).cross(mat2.get(ROW_2));
	if (axis.isZero() == false && AABBWithOBBAxisOverlap(aabb, obb, axis) == false) {
		return false;
	}
	axis = mat1.get(ROW_2).cross(mat2.get(ROW_0));
	if (axis.isZero() == false && AABBWithOBBAxisOverlap(aabb, obb, axis) == false) {
		return false;
	}
	axis = mat1.get(ROW_2).cross(mat2.get(ROW_1));
	if (axis.isZero() == false && AABBWithOBBAxisOverlap(aabb, obb, axis) == false) {
		return false;
	}
	axis = mat1.get(ROW_2).cross(mat2.get(ROW_2));
	if (axis.isZero() == false && AABBWithOBBAxisOverlap(aabb, obb, axis) == false) {
		return false;
	}
	return true;
}

float BENgineMathTools::ComputeAABBProjection(const CollisionVolumeAABB& aabb, const Vect& axis)
{
	//Vect v = axis * aabb.GetWorld().getInv();
	//return ((fabsf(v.X() * aabb.GetHalfDiagonal().X()) +
	//	fabsf(v.Y() * aabb.GetHalfDiagonal().Y()) + fabsf(v.Z() * aabb.GetHalfDiagonal().Z())) / axis.mag());

	return ((fabsf(axis.X() * aabb.GetHalfDiagonal().X()) +
		fabsf(axis.Y() * aabb.GetHalfDiagonal().Y()) + fabsf(axis.Z() * aabb.GetHalfDiagonal().Z())) / axis.mag());
}

bool BENgineMathTools::AABBWithOBBAxisOverlap(const CollisionVolumeAABB& aabb, const CollisionVolumeOBB& obb, const Vect& axis)
{
	const float d = fabsf((aabb.GetCenter().dot(axis) - obb.GetCenter().dot(axis)) / axis.mag());
	//const float p1 = ComputeAABBProjection(aabb, axis);
	//const float p2 = ComputeOBBProjection(obb, axis);
	//return d <= p1 + p2;

	const float p1p2 = ComputeAABBProjection(aabb, axis) + ComputeOBBProjection(obb, axis);
	return d <= p1p2;
	
}

bool BENgineMathTools::OBBToPointIntersect(const CollisionVolumeOBB& obb, const Vect& point)
{
    return ((obb.GetCornerMax().X() >= point.X()) && (point.X() >= obb.GetCornerMin().X()) &&
            (obb.GetCornerMax().Y() >= point.Y()) && (point.Y() >= obb.GetCornerMin().Y()) &&
            (obb.GetCornerMax().Z() >= point.Z()) && (point.Z() >= obb.GetCornerMin().Z()));
}

bool BENgineMathTools::OBBToOBBIntersect(const CollisionVolumeOBB& obb1, const CollisionVolumeOBB& obb2)
{
	//I use a bunch of if statements instead of a for loop to avoid having to compute the cross products unnecissarily
	//and to avoid storing variables when its not necessary.


	//maybe check all of the is zero values for the axes first and then do the axis overlap tests
    Vect axis;
    //Check the axes of the second OBB
    Matrix mat1 = obb2.GetWorld();
    axis = mat1.get(ROW_0);
    if (axis.isZero() == false && OBBAxisOverlap(obb1, obb2, axis) == false) {
        return false;
    }
    axis = mat1.get(ROW_1);
    if (axis.isZero() == false && OBBAxisOverlap(obb1, obb2, axis) == false) {
        return false;
    }
    axis = mat1.get(ROW_2);
    if (axis.isZero() == false && OBBAxisOverlap(obb1, obb2, axis) == false) {
        return false;
    }

	//Check the axes of the first OBB
    mat1 = obb1.GetWorld();
	axis = mat1.get(ROW_0);
    if (axis.isZero() == false && OBBAxisOverlap(obb1, obb2, axis) == false) {
        return false;
    }

    axis = mat1.get(ROW_1);

    if (axis.isZero() == false && OBBAxisOverlap(obb1, obb2, axis) == false) {
        return false;
    }

	axis = mat1.get(ROW_2);

    if (axis.isZero() == false && OBBAxisOverlap(obb1, obb2, axis) == false) {
        return false;
    }

	//Check the cross products of the axes
	const Matrix mat2 = obb2.GetWorld();
	axis = mat1.get(ROW_0).cross(mat2.get(ROW_0));
	if (axis.isZero() == false && OBBAxisOverlap(obb1, obb2, axis) == false) {
		return false;
	}
	axis = mat1.get(ROW_0).cross(mat2.get(ROW_1));
	if (axis.isZero() == false && OBBAxisOverlap(obb1, obb2, axis) == false) {
		return false;
	}
	axis = mat1.get(ROW_0).cross(mat2.get(ROW_2));
	if (axis.isZero() == false && OBBAxisOverlap(obb1, obb2, axis) == false) {
		return false;
	}
	axis = mat1.get(ROW_1).cross(mat2.get(ROW_0));
	if (axis.isZero() == false && OBBAxisOverlap(obb1, obb2, axis) == false) {
		return false;
	}
	axis = mat1.get(ROW_1).cross(mat2.get(ROW_1));
	if (axis.isZero() == false && OBBAxisOverlap(obb1, obb2, axis) == false) {
		return false;
	}
	axis = mat1.get(ROW_1).cross(mat2.get(ROW_2));
	if (axis.isZero() == false && OBBAxisOverlap(obb1, obb2, axis) == false) {
		return false;
	}
	axis = mat1.get(ROW_2).cross(mat2.get(ROW_0));
	if (axis.isZero() == false && OBBAxisOverlap(obb1, obb2, axis) == false) {
		return false;
	}
	axis = mat1.get(ROW_2).cross(mat2.get(ROW_1));
	if (axis.isZero() == false && OBBAxisOverlap(obb1, obb2, axis) == false) {
		return false;
	}
	axis = mat1.get(ROW_2).cross(mat2.get(ROW_2));
	if (axis.isZero() == false && OBBAxisOverlap(obb1, obb2, axis) == false) {
		return false;
	}
	return true;
}


float BENgineMathTools::ComputeOBBProjection(const CollisionVolumeOBB& obb, const Vect& axis)
{
	Vect v = axis * obb.GetWorld().getInv();
	return obb.GetScaleFactorSquared() * ((fabsf(v.X() * obb.GetHalfDiagonal().X()) +
           fabsf(v.Y() * obb.GetHalfDiagonal().Y()) + fabsf(v.Z() * obb.GetHalfDiagonal().Z())) / axis.mag());
}

bool BENgineMathTools::OBBAxisOverlap(const CollisionVolumeOBB& obb1, const CollisionVolumeOBB& obb2, const Vect& axis)
{
	const float d = fabsf((obb1.GetCenter().dot(axis) - obb2.GetCenter().dot(axis)) / axis.mag());
	//const float p1 = ComputeOBBProjection(obb1, axis);
	//const float p2 = ComputeOBBProjection(obb2, axis);
	//return d <= p1 + p2;
	const float p1p2 = ComputeOBBProjection(obb1, axis) + ComputeOBBProjection(obb2, axis);;

    return d <= p1p2;
}

