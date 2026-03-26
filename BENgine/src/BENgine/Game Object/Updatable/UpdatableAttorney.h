//Ben La Monica
#pragma once
#ifndef _UpdatableAttorney
#define _UpdatableAttorney

#include "Updatable.h"

class UpdatableAttorney
{
public:
	class GameLoop
	{
	private:
		friend class UpdatableManager;

		//Calls Updatable's Update() function. Called by the UpdatableManager each frame in ProcessElements().
		//Parameters:
		//up - the Updatable to call Update() on
		static void Update(Updatable* up) { up->Update();}
		
		//Returns the StorageEntryRef of the Updatable, which is used by the UpdatableManager to find and remove the Updatable from its storageList when it is deregistered.
		//Parameters:
		//up - the Updatable to get the StorageEntryRef of
		static UpdatableManager::StorageEntryRef GetStorageEntryRef(Updatable* up) { return up->GetStorageEntryRef(); }

		//Sets the StorageEntryRef of the Updatable, which is used by the UpdatableManager when it is added to the storageList.
		//Parameters:
		//up - the Updatable to set the StorageEntryRef of
		//entryRef - the StorageEntryRef to set the Updatable's StorageEntryRef to
		static void SetStorageEntryRef(Updatable* up, UpdatableManager::StorageEntryRef entryRef) { up->SetStorageEntryRef(entryRef); }
	};

public:
	class Registration
	{
		friend class UpdateRegistrationCommand;
		friend class UpdateDeregistrationCommand;

	private:
		static void SceneRegistration(Updatable* up) { up->SceneRegistration(); }
		static void SceneDeregistration(Updatable* up) { up->SceneDeregistration(); }
	};
};
#endif _UpdatableAttorney