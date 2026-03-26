#include "../../Scene/SceneManager.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneAttorney.h"
#include "DrawRegistrationCommand.h"
#include "DrawDeregistrationCommand.h"
#include "Drawable.h"

Drawable::Drawable()
{
	registrationCmd = new DrawRegistrationCommand(this);
	deregistrationCmd = new DrawDeregistrationCommand(this);

	//ALL X-ABLES START OFF DEREGISTERED
	curRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
}

Drawable::~Drawable()
{
	//Maybe add another enum here to specify it is being deleted
	//This would mean the RegistrationState enum has information
	//that isn't about registration.
	delete registrationCmd;
	delete deregistrationCmd;
}		 

void Drawable::SubmitDrawRegistration()
{
	assert(curRegistrationState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::Draw::SubmitCommand(SceneManager::GetCurrentScene(), registrationCmd);
	curRegistrationState = RegistrationState::PENDING_REGISTRATION;
}

void Drawable::SubmitDrawDeregistration()
{
	assert(curRegistrationState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::Draw::SubmitCommand(SceneManager::GetCurrentScene(), deregistrationCmd);
	curRegistrationState = RegistrationState::PENDING_DEREGISTRATION;
}

void Drawable::SetStorageEntryRef(DrawableManager::StorageEntryRef entryRef)
{
	storageEntryRef = entryRef;
}

DrawableManager::StorageEntryRef Drawable::GetStorageEntryRef()
{
	return storageEntryRef;
}

void Drawable::SceneRegistration()
{
	assert(curRegistrationState == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::Draw::Register(SceneManager::GetCurrentScene(), this);
	curRegistrationState = RegistrationState::CURRENTLY_REGISTERED;
}

void Drawable::SceneDeregistration()
{
	assert(curRegistrationState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::Draw::Deregister(SceneManager::GetCurrentScene(), this);
	curRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
}
