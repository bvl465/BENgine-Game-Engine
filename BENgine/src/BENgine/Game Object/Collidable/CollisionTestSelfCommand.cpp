#include "CollisionTestSelfCommand.h"
#include "CollidableGroup.h"
#include "CollisionDispatchBase.h"
#include "Collidable.h"
#include "../../Math Tools/BENgineMathTools.h"
#include "../../Collision/CollisionVolumeBSphere.h"
CollisionTestSelfCommand::CollisionTestSelfCommand(CollidableGroup* g1, CollisionDispatchBase* pd)
    : pG1(g1), pDispatch(pd)
{ }

CollisionTestSelfCommand::~CollisionTestSelfCommand()
{
    delete pDispatch; // Don’t forget!
}

void CollisionTestSelfCommand::Execute()
{
    const CollidableGroup::CollidableCollection& Collection1 = pG1->GetColliderCollection();

    for (auto it1 = Collection1.begin(); (it1) != Collection1.end(); it1++)
    {
        const CollisionVolume& cv1 = (*it1)->GetCollisionVolume();
		const CollisionVolumeBSphere& pBSphere1 = (*it1)->GetBSphere();
        for (auto it2 = std::next(it1, 1); it2 != Collection1.end(); it2++) // no repeat iterations
        {
            const CollisionVolumeBSphere& pBSphere2 = (*it2)->GetBSphere();

			if (!BENgineMathTools::BSphereToBSphereIntersect(pBSphere1, pBSphere2))
			{
				continue; // no intersection, skip to next
			}
            const CollisionVolume& cv2 = (*it2)->GetCollisionVolume();

            if (BENgineMathTools::Intersect(cv1, cv2))
            {
                pDispatch->ProcessCallbacks(*it1, *it2);
            }
        }
    }
}
