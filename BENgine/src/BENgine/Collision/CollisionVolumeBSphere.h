//Ben La Monica
#pragma once
#ifndef _CollisionVolumeBSphere
#define _CollisionVolumeBSphere

#include "CollisionVolume.h"
#include "Vect.h"

class CollisionVolumeAABB;
class Matrix;
class Model;

class CollisionVolumeBSphere : public CollisionVolume
{
private:
	float radius = 0.f;
	Vect center = Vect(0.f, 0.f, 0.f);
public:

	CollisionVolumeBSphere() = default;
	~CollisionVolumeBSphere() = default;
	CollisionVolumeBSphere(const CollisionVolumeBSphere&) = delete;
	CollisionVolumeBSphere& operator=(const CollisionVolumeBSphere&) = delete;

	//Draws a wire frame of this BSphere in the color passed.
	//Parameters:
	//color - the color to draw the wire frame of the BSphere in.
	virtual void DebugView(const Vect& color) const override;

	//Returns the center of the Bounding Sphere.
	inline const Vect& GetCenter() const
	{
		return center;
	};

	//Returns the radius of the Bounding Sphere.
	inline float GetRadius() const
	{
		return radius;
	};

	//Returns the radius squared of the Bounding Sphere.
	inline float GetRadiusSquared() const
	{
		return radius * radius;
	};

	//Computes the center and radius of the Bounding Sphere based on the Model and the world matrix passed.
	//Parameters:
	//mod - the Model to put the BSphere around.
	//mat - the world matrix to apply to the Model before computing the BSphere.
	virtual void ComputeData(Model& mod, const Matrix& mat) override;

	//Checks if this BSphere intersects with the BSphere passed. If they intersect this returns true, if they do not intersect this returns false.
	//Parameters:
	//other - the other CollisionVolumeBSphere to check for intersection with this CollisionVolumeBSphere.
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const override;

	//Checks if this BSphere intersects with the AABB passed. If they intersect this returns true, if they do not intersect this returns false.
	//Parameters:
	//other - the CollisionVolumeAABB to check for intersection with this CollisionVolumeBSphere.
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const override;

	//Checks if this BSphere intersects with the OBB passed. If they intersect this returns true, if they do not intersect this returns false.
	//Parameters:
	//other - the CollisionVolumeOBB to check for intersection with this CollisionVolumeBSphere.
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const override;

	//Checks if this BSphere intersects with the CollisionVolume passed. If they intersect this returns true, if they do not intersect this returns false.
	//Parameters:
	//other - the CollisionVolume to check for intersection with this CollisionVolumeBSphere.
	virtual bool IntersectAccept(const CollisionVolume& other) const override;

	//Returns the radius of this BSphere.
	virtual float GetBSphereRadiusFromCollisionVolume() const override;

	//Returns the center of this BSphere.
	virtual Vect GetBSphereCenterFromCollisionVolume() const override;

	//Sets the center and radius of the BSphere to the center and radius passed respectively.
	void SetCenterAndRadius(const Vect& c, float r);
};

#endif _CollisionVolumeBSphere