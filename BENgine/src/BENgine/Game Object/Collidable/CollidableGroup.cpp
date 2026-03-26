#include "CollidableGroup.h"
#include "CollidableAttorney.h"
#include "../../Collision/CollisionVolumeAABB.h"
#include "../../Collision/CollisionVolumeBSphere.h"

CollidableGroup::CollidableGroup() : groupAABB(new CollisionVolumeAABB())
{
}

CollidableGroup::~CollidableGroup()
{
    delete groupAABB;
}
const CollidableGroup::CollidableCollection& CollidableGroup::GetColliderCollection()
{
    return CollideCol;
}

void CollidableGroup::Register(Collidable* co)
{
    CollidableAttorney::GameLoop::SetStorageEntryRef(co, CollideCol.insert(CollideCol.end(), co));
}

void CollidableGroup::Deregister(Collidable* co)
{
    CollideCol.erase(CollidableAttorney::GameLoop::GetStorageEntryRef(co));
}

void CollidableGroup::UpdateGroupAABB()
{
	if (CollideCol.empty())
	{
		return;
	}
    Vect pBSCenter = (CollideCol.front())->GetBSphere().GetCenter();
    float pBSRadius = (CollideCol.front())->GetBSphere().GetRadius();
    float minX = pBSCenter.X() - pBSRadius;
    float minY = pBSCenter.Y() - pBSRadius;
    float minZ = pBSCenter.Z() - pBSRadius;

    float maxX = pBSCenter.X() + pBSRadius;
    float maxY = pBSCenter.Y() + pBSRadius;
    float maxZ = pBSCenter.Z() + pBSRadius;

    for (auto it = CollideCol.begin(); it != CollideCol.end(); it++)
    {
        const CollisionVolumeBSphere& pBS = (*it)->GetBSphere();
        pBSCenter = pBS.GetCenter();
        pBSRadius = pBS.GetRadius();
        const Vect tempMin = Vect(pBSCenter.X() - pBSRadius, pBSCenter.Y() - pBSRadius, pBSCenter.Z() - pBSRadius);
        const Vect tempMax = Vect(pBSCenter.X() + pBSRadius, pBSCenter.Y() + pBSRadius, pBSCenter.Z() + pBSRadius);
        if (tempMin.X() < minX) {
            minX = tempMin.X();
        }
        else if (tempMax.X() > maxX) {
            maxX = tempMax.X();
        }
        if (tempMin.Y() < minY) {
            minY = tempMin.Y();
        }
        else if (tempMax.Y() > maxY) {
            maxY = tempMax.Y();
        }
        if (tempMin.Z() < minZ) {
            minZ = tempMin.Z();
        }
        else if (tempMax.Z() > maxZ) {
            maxZ = tempMax.Z();
        }
    }
    groupAABB->SetMinMax(Vect(minX, minY, minZ), Vect(maxX, maxY, maxZ));
}

CollisionVolumeAABB& CollidableGroup::GetGroupAABB() const
{
    return *groupAABB;
}
