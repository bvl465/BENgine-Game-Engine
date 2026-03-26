//Ben La Monica
#pragma once
#ifndef _Drawable
#define _Drawable
#include "../RegistrationState.h"
#include "DrawableManager.h"
class DrawRegistrationCommand;
class DrawDeregistrationCommand;
class Drawable
{
public:
	Drawable();
	Drawable(const Drawable&) = delete;
	Drawable& operator=(const Drawable&) = delete;
	virtual ~Drawable();

protected:

	//Submits a DrawRegistrationCommand to the SceneRegistrationBroker to have it added to the DrawableManager's storageList to be drawn each frame.
	void SubmitDrawRegistration();

	//Submits a DrawDeregistrationCommand to the SceneRegistrationBroker to have it removed from the DrawableManager's storageList and stop being drawn each frame.
	void SubmitDrawDeregistration();

private:

	friend class DrawableAttorney;

	//Used for quick removal and quick access to the drawable in the DrawableManager.
	DrawableManager::StorageEntryRef storageEntryRef;

	//Used by the DrawableManager to set the StorageEntryRef of the Drawable when it is added to the storageList.
	//Parameters:
	//entryRef - the StorageEntryRef to set the Drawable's StorageEntryRef to
	void SetStorageEntryRef(DrawableManager::StorageEntryRef entryRef);

	//Returns the StorageEntryRef of the Drawable, which is used by the DrawableManager to find and remove the Drawable from its storageList when it is deregistered.
	DrawableManager::StorageEntryRef GetStorageEntryRef();


	//Used for rendering 3D objects, it is called BEFORE Draw2D() by DrawableManager in ProcessElements().
	//Defined by user.
	virtual void Draw() {};

	//Used for rendering sprites, it is called AFTER Draw() by DrawableManager in ProcessElements().
	//Defined by user.
	virtual void Draw2D() {};
	

	//Has the current Scene add the Drawable to the DrawableManager's storageList to be drawn each frame.
	void SceneRegistration();

	//Has the current Scene remove the Drawable from the DrawableManager's storageList to stop being drawn each frame.
	void SceneDeregistration();


	RegistrationState curRegistrationState;
	DrawRegistrationCommand* registrationCmd;
	DrawDeregistrationCommand* deregistrationCmd;

};
#endif _Drawable