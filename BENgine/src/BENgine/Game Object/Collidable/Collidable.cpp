#include "Collidable.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneAttorney.h"
#include "CollisionRegistrationCommand.h"
#include "CollisionDeregistrationCommand.h"
#include "../../Collision/CollisionVolumeBSphere.h"
#include "../../Collision/CollisionVolumeAABB.h"
#include "../../Collision/CollisionVolume.h"
#include "../../Collision/CollisionVolumeOBB.h"

Collidable::Collidable() : collisionVolume()
{
	pBSphere = new CollisionVolumeBSphere();
	registrationCmd = new CollisionRegistrationCommand(this);
	deregistrationCmd = new CollisionDeregistrationCommand(this);
	//ALL X-ABLES START OFF DEREGISTERED
	curRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
}

Collidable::~Collidable()
{
	curRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
	delete registrationCmd;
	delete deregistrationCmd; 
	delete collisionVolume;
	delete pBSphere;
}

const CollisionVolume& Collidable::GetCollisionVolume() const
{
	return *collisionVolume;
}

const CollisionVolumeBSphere& Collidable::GetBSphere()
{
	return *pBSphere;
}

void Collidable::SetStorageEntryRef(CollidableGroup::StorageEntryRef entryRef)
{
	storageEntryRef = entryRef;
}

CollidableGroup::StorageEntryRef Collidable::GetStorageEntryRef()
{
	return storageEntryRef;
}

void Collidable::SceneRegistration()
{
	assert(curRegistrationState == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::Collision::GetCollisionManager((SceneManager::GetCurrentScene()))->GetColGroup(myTypeID)->Register(this);
	curRegistrationState = RegistrationState::CURRENTLY_REGISTERED;
}

void Collidable::SceneDeregistration()
{
	assert(curRegistrationState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::Collision::GetCollisionManager((SceneManager::GetCurrentScene()))->GetColGroup(myTypeID)->Deregister(this);
	curRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Collidable::SetColliderModel(Model* model, VolumeType volumeType)
{
	if (collisionVolume != nullptr)
	{
		delete collisionVolume;
		collisionVolume = nullptr;
	}
	switch (volumeType)
	{
	case VolumeType::BSphere:
		collisionVolume = new CollisionVolumeBSphere();
		break;
	case VolumeType::AABB:
		collisionVolume = new CollisionVolumeAABB();
		break;
	case VolumeType::OBB:
		collisionVolume = new CollisionVolumeOBB();
		((CollisionVolumeOBB*)(collisionVolume))->InitializeOBBWithModel(*model);
		break;
	}
	pColModel = model;
}

void Collidable::UpdateCollisionData(const Matrix& mat)
{
	pBSphere->ComputeData(*pColModel, mat);
	collisionVolume->ComputeData(*pColModel, mat);
	//pBSphere->SetCenterAndRadius(collisionVolume->GetBSphereCenterFromCollisionVolume(), collisionVolume->GetBSphereRadiusFromCollisionVolume());
}

void Collidable::SubmitCollisionRegistration()
{
	assert(curRegistrationState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::Collision::SubmitCommand(SceneManager::GetCurrentScene(), registrationCmd);
	curRegistrationState = RegistrationState::PENDING_REGISTRATION;
}

void Collidable::SubmitCollisionDeregistration()
{
	assert(curRegistrationState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::Collision::SubmitCommand(SceneManager::GetCurrentScene(), deregistrationCmd);
	curRegistrationState = RegistrationState::PENDING_DEREGISTRATION;
}
