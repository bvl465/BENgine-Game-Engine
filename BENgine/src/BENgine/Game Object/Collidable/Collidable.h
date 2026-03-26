//Ben La Monica
#pragma once
#ifndef _Collidable
#define _Collidable
#include "../RegistrationState.h"
#include "CollisionManager.h"
#include "../../Scene/SceneAttorney.h"
#include "CollidableGroup.h"
#include "../../Collision/CollisionVolume.h"

class CollisionRegistrationCommand;
class CollisionDeregistrationCommand;
class CollisionVolumeBSphere;
class Collidable
{
public:
    Collidable();
    Collidable(const Collidable&) = delete;
    Collidable& operator=(const Collidable&) = delete;
    virtual ~Collidable();
	
	//Returns the CollisionVolume of the Collidable.
    const CollisionVolume& GetCollisionVolume() const;

	
    enum VolumeType {
        //Bounding Sphere
        BSphere,

		//Axis Aligned Bounding Box,
        AABB,

		//Oriented Bounding Box
		OBB
    };

	//Returns the Bounding Sphere of the Collidable.
    const CollisionVolumeBSphere& GetBSphere();
    
private:
    friend class CollidableAttorney;

    //The typeID of the Collidable used by the CollisionManager to determine which CollidableGroup the Collidable should be part of.
    CollisionManager::PWTypeID myTypeID = CollisionManager::PWID_UNDEFINED;

	//Used by the CollidableGroup to set the StorageEntryRef of the Collidable when it is added to the CollidableGroup's CollideCollection.
	//Parameters:
	//entryRef - the StorageEntryRef to set the Collidable's storageEntryRef to
    void SetStorageEntryRef(CollidableGroup::StorageEntryRef entryRef);

	//Returns the StorageEntryRef of the Collidable that is used by the CollidableGroup to remove the Collidable from the CollidableGroup's CollideCollection when it is deregistered.
    CollidableGroup::StorageEntryRef GetStorageEntryRef();

    CollidableGroup::StorageEntryRef storageEntryRef;

    void SceneRegistration();
    void SceneDeregistration();

    RegistrationState curRegistrationState;
    CollisionRegistrationCommand* registrationCmd;
    CollisionDeregistrationCommand* deregistrationCmd;


	CollisionVolume* collisionVolume = nullptr;
	CollisionVolumeBSphere* pBSphere = nullptr;

    Model* pColModel = nullptr;

protected:

    //Gets the typeID of the ColliderGroup that the Collidable should be part of from the CollisionManager
    template < typename C >
	void SetCollidableGroup() 
    {
        myTypeID = SceneAttorney::Collision::GetCollisionManager(SceneManager::GetCurrentScene())->GetTypeID<C>();
    }

	//Sets the model for the collidable to encapsulate and the type of collision volume to use for collision detection.
	//Parameters:
	//model - the model for the collidable to encapsulate. The collision volume will be based on the model's geometry.
	//volumeType - the type of collision volume to encapsulate the model in and use for collision detection.
    void SetColliderModel(Model* model, VolumeType volumeType);

	//Updates the collision volume's data based on the matrix passed.
	//Parameters:
	//mat - the matrix to update the collision volume with. Should be the world matrix of the model that the collidable is encapsulating.
    void UpdateCollisionData(const Matrix& mat);


    //Submits the Collidable for collision testing.
    void SubmitCollisionRegistration();

	//Removes the Collidable from collision testing.
    void SubmitCollisionDeregistration();

};

#endif _Collidable