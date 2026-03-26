//Ben La Monica
#pragma once
#ifndef _Updatable
#define _Updatable
#include "../RegistrationState.h"
#include "UpdatableManager.h"
class UpdateRegistrationCommand;
class UpdateDeregistrationCommand;
class Updatable
{
public:
	Updatable();
	Updatable(const Updatable&) = delete;
	Updatable& operator=(const Updatable&) = delete;
	virtual ~Updatable();

protected:

	//Submits an UpdateRegistrationCommand to the SceneRegistrationBroker to have it added to the UpdatableManager's storageList to be updated each frame.
	void SubmitUpdateRegistration();

	//Submits an UpdateDeregistrationCommand to the SceneRegistrationBroker to have it removed from the UpdatableManager's storageList and stop being updated each frame.
	void SubmitUpdateDeregistration();
	
private:

	friend class UpdatableAttorney;

	//Used for quick removal and quick access to the Updatable in the UpdatableManager.
	UpdatableManager::StorageEntryRef storageEntryRef;

	//Used by the UpdatableManager to set the StorageEntryRef of the Updatable when it is added to the storageList.
	//Parameters:
	//entryRef - the StorageEntryRef to set the Updatable's StorageEntryRef to
	void SetStorageEntryRef(UpdatableManager::StorageEntryRef entryRef);

	//Returns the StorageEntryRef of the Updatable, which is used by the UpdatableManager via UpdatableAttorney to find and remove the Updatable from its storageList when it is deregistered.
	UpdatableManager::StorageEntryRef GetStorageEntryRef() const;

	//Used for updating the Updatable each frame, it is called by the UpdatableManager in ProcessElements().
	//Defined by user.
	virtual void Update() {};

	//Has the current Scene add the Updatable to the UpdatableManager's storageList to be updated each frame
	void SceneRegistration();

	//Has the current Scene remove the Updatable from the UpdatableManager's storageList to stop being updated each frame.
	void SceneDeregistration();

	RegistrationState curRegistrationState;

	UpdateRegistrationCommand* registrationCmd;
	UpdateDeregistrationCommand* deregistrationCmd;

	

};
#endif _Updatable