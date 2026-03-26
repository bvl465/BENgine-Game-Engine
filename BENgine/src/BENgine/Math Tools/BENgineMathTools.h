#pragma once
#ifndef _BENgineMathTools
#define _BENgineMathTools

class Model;
class Matrix;
class Vect;


class BENgineMathTools;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class CollisionVolume;

class BENgineMathTools
{
public:
	BENgineMathTools() = default;
	~BENgineMathTools() = default;
	BENgineMathTools(const BENgineMathTools&) = delete;
	BENgineMathTools& operator=(const BENgineMathTools&) = delete;

	
	//Used as part of visitor pattern for collision detection. Returns true if the two CollisionVolumes intersect and false if they do not.
	//Parameters:
	//cv1 and cv2 - The two CollisionVolumes to check for collision between.
	static bool Intersect(const CollisionVolume& cv1, const CollisionVolume& cv2);

	//Returns true if the BSphere's intersect and false if they do not.
	//Parameters:
	//bs1 and bs2 - The two CollisionVolumeBSpheres to check for collision between.
	static bool BSphereToBSphereIntersect(const CollisionVolumeBSphere& bs1, const CollisionVolumeBSphere& bs2);

	//Returns true if the BSphere and Point intersect and false if they do not.
	//Parameters:
	//bs - The CollisionVolumeBSphere to check for collision with the point.
	//point - The point to check for collision with the BSphere.
	static bool BSphereToPointIntersect(const CollisionVolumeBSphere& bs, const Vect& point);

	//Returns true if the BSphere and OBB intersect and false if they do not.
	//Parameters:
	//bs - The CollisionVolumeBSphere to check for collision with the OBB.
	//obb - The CollisionVolumeOBB to check for collision with the BSphere.
	static bool BSphereToOBBIntersect(const CollisionVolumeBSphere& bs, const CollisionVolumeOBB& obb);

	//Returns true if the AABB and BSphere intersect and false if they do not.
	//Parameters:
	//aabb - The CollisionVolumeAABB to check for collision with the BSphere.
	//bs - The CollisionVolumeBSphere to check for collision with the AABB.
	static bool AABBToBSphereIntersect(const CollisionVolumeAABB& aabb, const CollisionVolumeBSphere& bs);

	//Returns true if the AABBs intersect and false if they do not.
	//Parameters:
	//aabb1 and aabb2 - The two CollisionVolumeAABBs to check for collision between.
	static bool AABBToAABBIntersect(const CollisionVolumeAABB& aabb1, const CollisionVolumeAABB& aabb2);

	//Returns true if the AABB and Point intersect and false if they do not.
	//Parameters:
	//aabb - The CollisionVolumeAABB to check for collision with the point.
	//point - The point to check for collision with the AABB.
	static bool AABBToPointIntersect(const CollisionVolumeAABB& aabb, const Vect& point);

	//Returns true if the AABB and OBB intersect and false if they do not.
	//Parameters:
	//aabb - The CollisionVolumeAABB to check for collision with the obb.
	//obb - The CollisionVolumeOBB to check for collision with the aabb.
	static bool AABBToOBBIntersect(const CollisionVolumeAABB& aabb, const CollisionVolumeOBB& obb);

	
	static float ComputeAABBProjection(const CollisionVolumeAABB& aabb, const Vect& axis);

	
	static bool AABBWithOBBAxisOverlap(const CollisionVolumeAABB& aabb, const CollisionVolumeOBB& obb, const Vect& axis);
	
	//Returns true if the OBB and Point intersect and false if they do not.
	//Parameters:
	//obb - The CollisionVolumeOBB to check for collision with the point.
	//point - The point to check for collision with the OBB.
	static bool OBBToPointIntersect(const CollisionVolumeOBB& obb, const Vect& point);

	//Returns true if the OBB and OBB intersect and false if they do not.
	//Parameters:
	//obb1 and obb2 - The two CollisionVolumeOBBs to check for collision between.
	static bool OBBToOBBIntersect(const CollisionVolumeOBB& obb1, const CollisionVolumeOBB& obb2);
	static float ComputeOBBProjection(const CollisionVolumeOBB& obb, const Vect& axis);
	static bool OBBAxisOverlap(const CollisionVolumeOBB& obb1, const CollisionVolumeOBB& obb2, const Vect& axis);

	static bool Overlap(const float min1, const float max1, const float min2, const float max2);
	

	static Vect VectClamp(const Vect v, const Vect min, const Vect max);
	static float FloatClamp(const float val, const float min, const float max);
	static int IntClamp(const int val, const int min, const int max);
	
};

#endif _BENgineMathTools
