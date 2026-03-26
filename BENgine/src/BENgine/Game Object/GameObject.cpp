#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneAttorney.h"
#include "./Life Cycle/GameObjectAttorney.h"
#include "./Life Cycle/GameObjectExitCommand.h"
#include "./Life Cycle/GameObjectEntryCommand.h"
#include "GameObject.h"

GameObject::GameObject()
{
	registrationCmd = new GameObjectEntryCommand(this);
	deregistrationCmd = new GameObjectExitCommand(this);
	curRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
}

GameObject::~GameObject()
{
	delete registrationCmd;
	delete deregistrationCmd;
}

void GameObject::SubmitEntry()
{
	assert(curRegistrationState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::GameObj::SubmitCommand(SceneManager::GetCurrentScene(), registrationCmd);
	//SceneManager::GetCurrentScene()->SubmitCommand(registrationCmd);
	curRegistrationState = RegistrationState::PENDING_REGISTRATION;
}

void GameObject::SubmitExit()
{
	if (curRegistrationState != RegistrationState::PENDING_DEREGISTRATION) {

		assert(curRegistrationState == RegistrationState::CURRENTLY_REGISTERED);
		//SceneManager::GetCurrentScene()->SubmitCommand(deregistrationCmd);
		SceneAttorney::GameObj::SubmitCommand(SceneManager::GetCurrentScene(), deregistrationCmd);

		curRegistrationState = RegistrationState::PENDING_DEREGISTRATION;
	}
	//if it is pending deregistration don't waste time with another command and also don't throw an error

}

void GameObject::ConnectToScene()
{
	assert(curRegistrationState == RegistrationState::PENDING_REGISTRATION);
	
	curRegistrationState = RegistrationState::CURRENTLY_REGISTERED;
	this->SceneEntry();
}

void GameObject::DisconnectFromScene()
{
	assert(curRegistrationState == RegistrationState::PENDING_DEREGISTRATION);
	

	//SceneManager::GetCurrentScene()->Deregister(this);
	curRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
	this->SceneExit();
}
