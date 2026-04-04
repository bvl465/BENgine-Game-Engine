//Ben La Monica
#pragma once
#ifndef _CollisionVolumeOBB
#define _CollisionVolumeOBB

#include "CollisionVolume.h"
#include "Vect.h"

class Matrix;
class Model;

class CollisionVolumeOBB : public CollisionVolume
{
private:

	float scaleFactorSquared = 1.f;
	Matrix world;
	Vect cornerMax;
	Vect cornerMin;
	Vect halfDiagonal;
	Vect center;

	


public:

	CollisionVolumeOBB() = default;
	~CollisionVolumeOBB() = default;
	CollisionVolumeOBB(const CollisionVolumeOBB&) = delete;
	CollisionVolumeOBB& operator=(const CollisionVolumeOBB&) = delete;

	//Returns the corner of the OBB with the smallest x, y, and z values.
	const Vect& GetCornerMin() const
	{
		return cornerMin;
	};

	//Returns the corner of the OBB with the largest x, y, and z values.
	const Vect& GetCornerMax() const
	{
		return cornerMax;
	};

	//Returns the world matrix of the OBB.
	const Matrix& GetWorld() const
	{
		return world;
	};

	//Returns the center of the OBB.
	const Vect& GetCenter() const
	{
		return center;
	};

	//Returns the half diagonal of the OBB .5f(cornerMax - cornerMin).
	const Vect& GetHalfDiagonal() const
	{
		return halfDiagonal;
	};

	//Returns the scale factor squared of the OBB.
	const float GetScaleFactorSquared() const
	{
		return scaleFactorSquared;
	};


	//Computes the cornerMin, cornerMax, center, and halfDiagonal of the OBB based on the Model and the world matrix passed.
	//Parameters:
	//mod - the Model to put the OBB around.
	//mat - the world matrix to apply to the Model before computing the OBB.
	virtual void ComputeData(Model& mod, const Matrix& mat) override;



	//Checks if this OBB intersects with the BSphere passed. If they intersect this returns true, if they do not intersect this returns false.
	//Parameters:
	//other - the CollisionVolumeBSphere to check for intersection with this CollisionVolumeOBB.
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const override;

	//Checks if this OBB intersects with the AABB passed. If they intersect this returns true, if they do not intersect this returns false.
	//Parameters:
	//other - the CollisionVolumeAABB to check for intersection with this CollisionVolumeOBB.
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const override;

	//Checks if this OBB intersects with the OBB passed. If they intersect this returns true, if they do not intersect this returns false.
	//Parameters:
	//other - the CollisionVolumeOBB to check for intersection with this CollisionVolumeOBB.
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const override;

	//Checks if this OBB intersects with the CollisionVolume passed. If they intersect this returns true, if they do not intersect this returns false.
	//Parameters:
	//other - the CollisionVolume to check for intersection with this CollisionVolumeOBB.
	virtual bool IntersectAccept(const CollisionVolume& other) const override;

	//Sets the data of the OBB based on the Model passed. This does not update the world matrix of the OBB.
	//Parameters:
	//mod - the Model to put the OBB around.
	void InitializeOBBWithModel(const Model& mod);


	//Draws a wire frame of this OBB in the color passed.
	//Parameters:
	//color - the color to draw the wire frame of the OBB in.
	virtual void DebugView(const Vect& color) const override;

	//Returns the radius of the Bounding Sphere that would enclose this OBB.
	virtual float GetBSphereRadiusFromCollisionVolume() const override;

	//Returns the center of the Bounding Sphere that would enclose this OBB.
	virtual Vect GetBSphereCenterFromCollisionVolume() const override;


};

#endif _CollisionVolumeOBB