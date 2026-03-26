#include "CollisionTestPairCommand.h"
#include "CollidableGroup.h"
#include "CollisionDispatchBase.h"
#include "Collidable.h"
#include "../../Collision/CollisionVolumeBSphere.h"
#include "../../Collision/CollisionVolumeAABB.h"

//#include "../../Collision/CollisionVolumeBSphere.h"
#include "../../Math Tools/BENgineMathTools.h"


CollisionTestPairCommand::CollisionTestPairCommand(CollidableGroup* g1, CollidableGroup* g2, CollisionDispatchBase* pd)
	: pG1(g1), pG2(g2), pDispatch(pd)
{

}

CollisionTestPairCommand::~CollisionTestPairCommand()
{
	//delete pG1AABB;
	//delete pG2AABB;
    delete pDispatch; // Don’t forget!
}

void CollisionTestPairCommand::Execute()
{
    const CollidableGroup::CollidableCollection& Collection1 = pG1->GetColliderCollection();
    const CollidableGroup::CollidableCollection& Collection2 = pG2->GetColliderCollection();

	if (Collection1.empty() || Collection2.empty())
	{
		return; //if either list is empty then GET OUT!!!
	}

    //check if aabb collides------------------------------
	if (BENgineMathTools::AABBToAABBIntersect(pG1->GetGroupAABB(), pG2->GetGroupAABB()) == false)
	{
        pG1->GetGroupAABB().DebugView(Vect(1.0f, 0.0f, 0.0f));
        pG2->GetGroupAABB().DebugView(Vect(1.0f, 0.0f, 0.0f));
        //pG2AABB->DebugView(Vect(1.0f, 0.0f, 0.0f));

		return; //if the AABBs don't intersect then GET OUT!!!
	}
    //-----------------------------------------------------------

    pG1->GetGroupAABB().DebugView(Vect(.0f, 1.0f, 0.0f));
    pG2->GetGroupAABB().DebugView(Vect(.0f, 1.0f, 0.0f));
    //pG2AABB->DebugView(Vect(.0f, 1.0f, 0.0f));


    for (auto it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
    {
        const CollisionVolumeBSphere& pBS1 = (*it1)->GetBSphere();
        if (BENgineMathTools::AABBToBSphereIntersect(pG1->GetGroupAABB(), pBS1) == false)
        {
            continue;
        }
        for (auto it2 = Collection2.begin(); it2 != Collection2.end(); it2++)
        {
            const CollisionVolumeBSphere& pBS2 = (*it2)->GetBSphere();
            if (BENgineMathTools::BSphereToBSphereIntersect(pBS2, pBS1) == false)
            {
                continue;
            }
            const CollisionVolume& cv1 = (*it1)->GetCollisionVolume();
            const CollisionVolume& cv2 = (*it2)->GetCollisionVolume();
            if (BENgineMathTools::Intersect(cv1, cv2))
            {
                pDispatch->ProcessCallbacks(*it1, *it2);
            }
        }
    }
}
