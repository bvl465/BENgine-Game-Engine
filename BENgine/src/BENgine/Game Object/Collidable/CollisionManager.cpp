#include "CollisionManager.h"
#include "CollidableAttorney.h"
#include "CollisionTestCommandBase.h"
#include "CollidableGroup.h"

CollisionManager::PWTypeID CollisionManager::TypeIDNextNumber = 0;

CollisionManager::CollisionManager() : ColGroupCollection(MAX_COLLISION_GROUP, nullptr) {}

CollisionManager::~CollisionManager()
{
    for each (CollidableGroup* cg in ColGroupCollection)
    {
        if (cg != nullptr) {
            delete cg;
        }
        
    }
    ColGroupCollection.clear();

    for each (CollisionTestCommandBase* ct in colTestCommands)
    {
        if (ct != nullptr) {
            delete ct;
        }

    }
    colTestCommands.clear();
}

void CollisionManager::ProcessCollisions()
{
    for (std::size_t i = 0; i < ColGroupCollection.size(); i++) 
    {
		if (ColGroupCollection[i] != nullptr)
		{
			ColGroupCollection[i]->UpdateGroupAABB();
		}
	}
    //go through active collidable groups and calculate their aabb using the same method as that in test pair.
    for (CollisionTestCommands::iterator it = colTestCommands.begin(); it != colTestCommands.end(); it++) {
        (*it)->Execute();
    }
    //for (CollisionTestCommands::iterator it = colTestCommands.begin(); it != colTestCommands.end(); it++) {
    //    (*it)->Execute();
    //}

}


void CollisionManager::SetGroupForTypeID(CollisionManager::PWTypeID ind)
{
    if (ColGroupCollection[ind] == nullptr)
    {
        ColGroupCollection[ind] = new CollidableGroup();
    }
}


CollidableGroup* CollisionManager::GetColGroup(PWTypeID id)
{
    return ColGroupCollection[id];
}