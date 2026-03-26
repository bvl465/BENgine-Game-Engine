#pragma once
#ifndef _CollisionVolume
#define _CollisionVolume

#include "../Visualizer/Visualizer.h"
class Model;
class Matrix;


class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;


class CollisionVolume
{

private:
	
public:

	CollisionVolume() = default;
	virtual ~CollisionVolume() = default;
	CollisionVolume(const CollisionVolume&) = delete;
	CollisionVolume& operator=(const CollisionVolume&) = delete;
	virtual void DebugView(const Vect& color) const = 0;
	virtual void ComputeData(Model& mod, const Matrix& mat) = 0;


	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const = 0;

	virtual bool IntersectAccept(const CollisionVolume& other) const = 0;
	virtual float GetBSphereRadiusFromCollisionVolume() const = 0;
	virtual Vect GetBSphereCenterFromCollisionVolume() const = 0;
};

#endif _CollisionVolume
