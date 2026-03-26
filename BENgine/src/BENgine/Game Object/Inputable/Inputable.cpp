#include "../../Scene/SceneManager.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneAttorney.h"
#include "InputRegistrationCommand.h"
#include "InputDeregistrationCommand.h"
#include "Inputable.h"

Inputable::Inputable()
{

	//registrationCmd = new InputRegistrationCommand(this);
	//deregistrationCmd = new InputDeregistrationCommand(this);

	//ALL X-ABLES START OFF DEREGISTERED
}

Inputable::~Inputable()
{
	for (RegistrationDataMap::iterator it = regDataMap.begin(); it != regDataMap.end(); it++) {
		it->second.curRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
		delete it->second.registrationCmd;
		delete it->second.deregistrationCmd;

		//If I make registration data a pointer in the registration data map then this is what it will look like
		//delete (it->second)->registrationCmd;
		//delete (it->second)->deregistrationCmd;
		
	}
	regDataMap.clear();
	//Maybe add another enum here to specify it is being deleted
	//This would mean the RegistrationState enum has information
	//that isn't about registration.
}

void Inputable::SetStorageEntryRef(AZUL_KEY key, KeyEvent ke, SingleKeyEventManager::StorageEntryRef entryRef)
{
	regDataMap.find(KeyEventPair(key, ke))->second.storageEntryRef = entryRef;
}

SingleKeyEventManager::StorageEntryRef Inputable::GetStorageEntryRef(AZUL_KEY key, KeyEvent ke) const
{
	return (regDataMap.find(KeyEventPair(key, ke))->second).storageEntryRef;
}


void Inputable::SubmitKeyRegistration(AZUL_KEY key, KeyEvent ke)
{
	RegistrationDataMap::iterator it = regDataMap.find(KeyEventPair(key, ke));
	RegistrationData regData;
	if (it == regDataMap.end()) {
		regData.registrationCmd = new InputRegistrationCommand(this, key, ke);
		regData.deregistrationCmd = new InputDeregistrationCommand(this, key, ke);
		regData.curRegistrationState = RegistrationState::PENDING_REGISTRATION;
		regDataMap.insert({ KeyEventPair(key,ke), regData });

		
	}
	else {
		assert(it->second.curRegistrationState == RegistrationState::CURRENTLY_DEREGISTERED); 
		regData = it->second;
		regData.curRegistrationState = RegistrationState::PENDING_REGISTRATION;
		
	}

	SceneAttorney::Input::SubmitCommand(SceneManager::GetCurrentScene(), regData.registrationCmd);

}

void Inputable::SubmitKeyDeregistration(AZUL_KEY key, KeyEvent ke)
{
	//I only have this because the engine is run in debug and I don't want to search for each assert
	RegistrationDataMap::iterator it = regDataMap.find(KeyEventPair(key, ke));
	assert(it != regDataMap.end()); //If it is deregistered it shouldn't be deregistered again
	assert(it->second.curRegistrationState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::Input::SubmitCommand(SceneManager::GetCurrentScene(), it->second.deregistrationCmd);
	it->second.curRegistrationState = RegistrationState::PENDING_DEREGISTRATION;
}



void Inputable::SceneRegistration(AZUL_KEY key, KeyEvent ke)
{
	//I only have this because the engine is run in debug and I don't want to search for each assert
	RegistrationDataMap::iterator it = regDataMap.find(KeyEventPair(key, ke));
	
	assert(it != regDataMap.end());
	assert(it->second.curRegistrationState == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::Input::Register(SceneManager::GetCurrentScene(), this, key, ke);
	regDataMap.find(KeyEventPair(key, ke))->second.curRegistrationState = RegistrationState::CURRENTLY_REGISTERED;
}

void Inputable::SceneDeregistration(AZUL_KEY key, KeyEvent ke)
{
	//I only have this because the engine is run in debug and I don't want to search for each assert
	RegistrationDataMap::iterator it = regDataMap.find(KeyEventPair(key, ke));
	assert(it != regDataMap.end());
	assert(it->second.curRegistrationState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::Input::Deregister(SceneManager::GetCurrentScene(), this, key, ke);
	it->second.curRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;

	//Rather than delete the registration data I opted to just change its state
	//and reuse it. This is because I don't want to have to create a new one every time
	//which could result in rebalancing the map.
}

