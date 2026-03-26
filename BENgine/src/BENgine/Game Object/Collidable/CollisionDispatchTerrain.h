#ifndef _CollisionDispatchTerrain
#define _CollisionDispatchTerrain
#include "CollisionDispatchBase.h"

//Calls CollisionTerrain() on the Collidable
//Parameters:
//C1 - the Collidable to call CollisionTerrain() on
template <typename C1>
class CollisionDispatchTerrain : public CollisionDispatchBase
{
public:

    CollisionDispatchTerrain() = default;
    CollisionDispatchTerrain(const CollisionDispatchTerrain&) = delete;
    CollisionDispatchTerrain& operator=(const CollisionDispatchTerrain&) = delete;
    virtual ~CollisionDispatchTerrain() = default;

    //Calls Collision on both Collidables with the other Collidable as the parameter.
    //Parameters:
    //c1 - the first Collidable to call Collision() on
	//c2 - unused for terrain collisions but is required to match the CollisionDispatchBase
    virtual void ProcessCallbacks(Collidable* c1, Collidable* c2)
    {
        c2;
        // See also http://www.drdobbs.com/casting-in-c/184403316

        C1* pDerCol1 = static_cast<C1*>(c1);

        pDerCol1->CollisionTerrain();
    }
};

#endif _CollisionDispatchTerrain