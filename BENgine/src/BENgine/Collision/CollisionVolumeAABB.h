//Ben La Monica
#pragma once
#ifndef _CollisionVolumeAABB
#define _CollisionVolumeAABB

#include "CollisionVolume.h"
#include "Vect.h"

class Matrix;
class Model;

class CollisionVolumeAABB : public CollisionVolume
{
private:

	//Lots of wasted memory from 12 bytes of padding after the virtual pointer.
	//Also may be better to not store the center and just add the half diagonal to 
	//the cornerMin to get the center when needed. Additionally 

	Matrix world;
	Vect cornerMax;
	Vect cornerMin;

	Vect halfDiagonal;

	Vect center;

public:

	CollisionVolumeAABB() = default;
	~CollisionVolumeAABB() = default;
	CollisionVolumeAABB(const CollisionVolumeAABB&) = default;
	CollisionVolumeAABB& operator=(const CollisionVolumeAABB&) = default;


	//Returns the corner of the AABB with the smallest x, y, and z values.
	const Vect& GetCornerMin() const;

	//Returns the corner of the AABB with the largest x, y, and z values.
	const Vect& GetCornerMax() const;

	//Returns the world matrix of the AABB.
	const Matrix& GetWorld() const;

	//Returns the center of the AABB.
	const Vect& GetCenter() const;

	//Returns the half diagonal of the AABB .5f(cornerMax - cornerMin).
	const Vect& GetHalfDiagonal() const;

	//Computes the cornerMin, cornerMax, center, and halfDiagonal of the AABB based on the Model and the world matrix passed.
	//Parameters:
	//mod - the Model to put the AABB around.
	//mat - the world matrix to apply to the Model before computing the AABB.
	virtual void ComputeData(Model& mod, const Matrix& mat) override;

	//Checks if this AABB intersects with the BSphere passed. If they intersect this returns true, if they do not intersect this returns false.
	//Parameters:
	//other - the CollisionVolumeBSphere to check for intersection with this CollisionVolumeAABB.
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const override;

	//Checks if this AABB intersects with the AABB passed. If they intersect this returns true, if they do not intersect this returns false.
	//Parameters:
	//other - the other CollisionVolumeAABB to check for intersection with this CollisionVolumeAABB.
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const override;

	//Checks if this AABB intersects with the OBB passed. If they intersect this returns true, if they do not intersect this returns false.
	//Parameters:
	//other - the CollisionVolumeOBB to check for intersection with this CollisionVolumeAABB.
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const override;

	//Checks if this AABB intersects with the CollisionVolume passed. If they intersect this returns true, if they do not intersect this returns false.
	//Parameters:
	//other - the CollisionVolume to check for intersection with this CollisionVolumeAABB.
	virtual bool IntersectAccept(const CollisionVolume& other) const override;


	//Draws a wire frame of this AABB in the color passed.
	//Parameters:
	//color - the color to draw the wire frame of the AABB in.
	virtual void DebugView(const Vect& color) const override;

	//Sets the cornerMin and cornerMax of the AABB to the min and max passed respectively.
	//Parameters:
	//min - the Vect to set the cornerMin of the AABB to.
	//max - the Vect to set the cornerMax of the AABB to.
	void SetMinMax(const Vect& min, const Vect& max);

	//Returns the radius of the Bounding Sphere that would encompass this AABB.
	virtual float GetBSphereRadiusFromCollisionVolume() const override;

	//Returns the center of the Bounding Sphere that would encompass this AABB.
	virtual Vect GetBSphereCenterFromCollisionVolume() const override;
};

#endif _CollisionVolumeAABB