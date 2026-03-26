#pragma once
#ifndef _CollisionManager
#define _CollisionManager

#include <vector>
#include <list>
#include "CollisionDispatch.h"
#include "CollisionDispatchTerrain.h"
#include "CollisionTestPairCommand.h"
#include "CollisionTestSelfCommand.h"
#include "CollisionTestTerrainCommand.h"
class CollidableGroup;
class CollisionTestCommandBase;
class CollisionManager
{
public:

    CollisionManager();
    CollisionManager(const CollisionManager&) = delete;
    CollisionManager& operator=(const CollisionManager&) = delete;
    ~CollisionManager();

    void ProcessCollisions();

    using PWTypeID = int;


    static const PWTypeID PWID_UNDEFINED = -1;



    CollidableGroup* GetColGroup(PWTypeID id);


    template <typename C>
    PWTypeID GetTypeID()
    {
        static PWTypeID myTypeID = TypeIDNextNumber++;
    
        SetGroupForTypeID(myTypeID);
    
        //DebugMsg::out("CollisionManager: TypeID %d registered\n", myTypeID);
        return myTypeID;
    }
private:


    const int MAX_COLLISION_GROUP = 64;

    static PWTypeID TypeIDNextNumber;


    using CollidableGroupCollection = std::vector<CollidableGroup*>;

    CollidableGroupCollection ColGroupCollection;


    void SetGroupForTypeID(CollisionManager::PWTypeID ind);


private:
    using CollisionTestCommands = std::list<CollisionTestCommandBase*>;
    CollisionTestCommands colTestCommands;

public:

    //Sets up collision detection between two types of collidables.
    //Parameters:
    //C1 - The first collidable type. Must implement Collision(*C2)
    //C2 - The second collidable type. Must implement Collision(*C1)
    template< typename C1, typename C2>
    void SetCollisionPair()
    {
        CollidableGroup* pg1 = ColGroupCollection[GetTypeID<C1>()];
        CollidableGroup* pg2 = ColGroupCollection[GetTypeID<C2>()];

        CollisionDispatch<C1, C2>* pDispatch = new CollisionDispatch<C1, C2>();

        colTestCommands.push_back(new CollisionTestPairCommand(pg1, pg2, pDispatch));
    }

    //Sets up collision detection with a single type of collidable with itself.
    //Parameters:
    //C - The collidable type to test for collision with others of its type.
    template <typename C>
    void SetCollisionSelf()
    {
        CollidableGroup* pG = ColGroupCollection[GetTypeID<C>()];
        CollisionDispatch<C, C>* pDispatch = new CollisionDispatch<C, C>();
        colTestCommands.push_back(new CollisionTestSelfCommand(pG, pDispatch));
    }


    //Sets up collision detection between a type of collidables and the terrain that is within the terrain manager. If a terrain is not set when this is called the engine will crash. This is intentional.
    //Parameters:
    //C - The collidable type to test for collision with the terrain. Must implement CollisionTerrain()
    template <typename C>
    void SetCollisionTerrain()
    {
        CollidableGroup* pG = ColGroupCollection[GetTypeID<C>()];
        CollisionDispatchTerrain<C>* pDispatch = new CollisionDispatchTerrain<C>();
        colTestCommands.push_back(new CollisionTestTerrainCommand(pG, pDispatch));
    }

};

#endif _CollisionManager