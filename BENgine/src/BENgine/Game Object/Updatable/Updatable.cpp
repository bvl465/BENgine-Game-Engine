#include "../../Scene/SceneManager.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneAttorney.h"
#include "UpdateRegistrationCommand.h"
#include "UpdateDeregistrationCommand.h"
#include "Updatable.h"

Updatable::Updatable()
{
	registrationCmd = new UpdateRegistrationCommand(this);
	deregistrationCmd = new UpdateDeregistrationCommand(this);
	curRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
}

Updatable::~Updatable()
{
	delete registrationCmd;
	delete deregistrationCmd;
}

void Updatable::SubmitUpdateRegistration()
{
	assert(curRegistrationState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::Update::SubmitCommand(SceneManager::GetCurrentScene(), registrationCmd);
	curRegistrationState = RegistrationState::PENDING_REGISTRATION;
	
}

void Updatable::SubmitUpdateDeregistration()
{
	assert(curRegistrationState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::Update::SubmitCommand(SceneManager::GetCurrentScene(), deregistrationCmd);

	curRegistrationState = RegistrationState::PENDING_DEREGISTRATION;
}

void Updatable::SetStorageEntryRef(UpdatableManager::StorageEntryRef entryRef)
{
	storageEntryRef = entryRef;
}

UpdatableManager::StorageEntryRef Updatable::GetStorageEntryRef() const
{
	return storageEntryRef;
}

void Updatable::SceneRegistration()
{
	assert(curRegistrationState == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::Update::Register(SceneManager::GetCurrentScene(), this);

	//SceneManager::GetCurrentScene()->Register(this);
	curRegistrationState = RegistrationState::CURRENTLY_REGISTERED;
}

void Updatable::SceneDeregistration()
{
	assert(curRegistrationState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::Update::Deregister(SceneManager::GetCurrentScene(), this);

	//SceneManager::GetCurrentScene()->Deregister(this);
	curRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
}
