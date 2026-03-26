#ifndef _CollisionDispatch
#define _CollisionDispatch
#include "CollisionDispatchBase.h"

//Calls Collision() on both Collidables with the other Collidable as the parameter.
//Parameters:
//C1 - the first Collidable to call Collision() on
//C2 - the second Collidable to call Collision() on
template <typename C1, typename C2>
class CollisionDispatch : public CollisionDispatchBase
{
public:

    CollisionDispatch() = default;
    CollisionDispatch(const CollisionDispatch&) = delete;
    CollisionDispatch& operator=(const CollisionDispatch&) = delete;
    virtual ~CollisionDispatch() = default;

	//Calls Collision on both Collidables with the other Collidable as the parameter.
	//Parameters:
	//c1 - the first Collidable to call Collision() on
	//c2 - the second Collidable to call Collision() on
    virtual void ProcessCallbacks(Collidable* c1, Collidable* c2)
    {
        // See also http://www.drdobbs.com/casting-in-c/184403316
        C1* pDerCol1 = static_cast<C1*>(c1);
        C2* pDerCol2 = static_cast<C2*>(c2);

        pDerCol1->Collision(pDerCol2);
        pDerCol2->Collision(pDerCol1);
    }
};

#endif _CollisionDispatch