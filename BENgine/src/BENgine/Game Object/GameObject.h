//Ben La Monica
#pragma once
#ifndef _GameObject
#define _GameObject
#include "./Drawable/Drawable.h"
#include "./Updatable/Updatable.h"
#include "./Alarmable/Alarmable.h"
#include "./Inputable/Inputable.h"
#include "./Collidable/Collidable.h"
class GameObjectEntryCommand;
class GameObjectExitCommand;
class GameObject : public Collidable,public Inputable, public Drawable,  public Updatable, public Alarmable
{
public:
	GameObject();
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;
	virtual ~GameObject();
	void SubmitEntry();
	void SubmitExit();
private:
	friend class GameObjectAttorney;
	RegistrationState curRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
	GameObjectEntryCommand* registrationCmd;
	GameObjectExitCommand* deregistrationCmd;
	virtual void SceneEntry() {};
	virtual void SceneExit() {};
	void ConnectToScene();
	void DisconnectFromScene();
};
#endif _GameObject