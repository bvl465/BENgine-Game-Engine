//Ben La Monica
#pragma once
#ifndef _Inputable
#define _Inputable
#include "../RegistrationState.h"
#include "KeyEvent.h"
#include "SingleKeyEventManager.h"
#include "AzulCore.h"
#include <map>
class InputRegistrationCommand;
class InputDeregistrationCommand;
class Inputable
{
public:


protected:
	Inputable();
	Inputable(const Inputable&) = delete;
	Inputable& operator=(const Inputable&) = delete;
	virtual ~Inputable();
	
	//Submits an InputRegistrationCommand to the SceneRegistrationBroker to have the Inputable added to the InputableList for KeyEvent ke in the SingleKeyEventManager of AZUL_KEY key to have the Inputable method for KeyEvent ke to be called when the key is in that state.
	//Parameters:
	//key - the AZUL_KEY to register for
	//ke - the KeyEvent to register for
	void SubmitKeyRegistration(AZUL_KEY key, KeyEvent ke);

	//Submits an InputDeregistrationCommand to the SceneRegistrationBroker to have the Inputable removed from the InputableList for KeyEvent ke in the SingleKeyEventManager of AZUL_KEY key to stop having the Inputable method for KeyEvent ke called when AZUL_KEY key is in that state.
	//Parameters:
	//key - the AZUL_KEY to deregister for
	//ke - the KeyEvent to deregister for
	void SubmitKeyDeregistration(AZUL_KEY key, KeyEvent ke);

	//Called by SingleKeyEventManager of AZUL_KEY key the frame that key is pressed if the key was up or released during the previous frame.
	//Parameters:
	//key - the AZUL_KEY that was pressed
	virtual void KeyPress(AZUL_KEY key) { key; }

	//Called the frame that AZUL_KEY key is released if the key was down or pressed during the previous frame.
	//Parameters:
	//key - the AZUL_KEY that was released
	virtual void KeyRelease(AZUL_KEY key) { key; }

	//Called when AZUL_KEY key is down and was pressed or down the previous frame
	//Parameters:
	//key - the AZUL_KEY that is down
	virtual void KeyDown(AZUL_KEY key) { key; }

	//Called when AZUL_KEY key is up and was released or up during the previous frame
	//Parameters:
	//key - the AZUL_KEY that is up
	virtual void KeyUp(AZUL_KEY key) { key; }
private:

	friend class InputableAttorney;
	
	//inputable says to key board manager register me for x key
	//keyboard manager checks if it has that single key event manager and if it does
	//then it appropriately registers it. If not it creates the manager and then
	//registers it to the list in the single key event manager that corresponds with
	//the key event.
	//

	struct RegistrationData {
		InputRegistrationCommand* registrationCmd = nullptr;
		InputDeregistrationCommand* deregistrationCmd = nullptr;

		//Not sure if the delete ref should be an iterator of the single key event
		// manager itself so as to prevent a search of single key events every time
		// or if it should be just be the iterator of itself in the single key event
		// manager. It comes down to if there will be more single key event managers
		// than there are inputables in the single key event manager. I am going to store
		// the inputables in a list in the single key event manager since they all
		// have to have their respective key press or release command called anyways
		// so fast access isn't necessary. Since access is crucial for the keyboard event
		// manager I will store the single key event managers in a map in the keyboard
		// event manager. This means I will already have fast access to the single key event
		// managers.

		//The storageEntryRef of the Inputable in the InputableList associated with the KeyEvent located in the SingleKeyEventManager for the AZUL_KEY of the KeyEventpair.
		SingleKeyEventManager::StorageEntryRef storageEntryRef;
		RegistrationState curRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
	};


	using KeyEventPair = std::pair<AZUL_KEY, KeyEvent>;


	using RegistrationDataMap = std::multimap<KeyEventPair, RegistrationData>;

	//Map of the registration data for each KeyEventPair that the Inputable ever registered for.
	RegistrationDataMap regDataMap;
	
	//Sets the storageEntryRef of the KeyEventPair in the RegistrationDataMap to the entryRef passed in.
	//Parameters:
	//key - the AZUL_KEY of the KeyEventPair to set the storageEntryRef of
	//ke - the KeyEvent of the KeyEventPair to set the storageEntryRef of
	//entryRef - the StorageEntryRef to set the storageEntryRef of the KeyEventPair with the AZUL_KEY key and KeyEvent ke to
	void SetStorageEntryRef(AZUL_KEY key, KeyEvent ke, SingleKeyEventManager::StorageEntryRef entryRef);

	//Returns the storageEntryRef of the KeyEventPair in the RegistrationDataMap. This is used by the SingleKeyEventManager for AZUL_KEY k to find and remove the Inputable from the InputableList associated with the KeyEvent ke when deregistered.
	SingleKeyEventManager::StorageEntryRef GetStorageEntryRef(AZUL_KEY key, KeyEvent ke) const;

	void SceneRegistration(AZUL_KEY key, KeyEvent ke);
	void SceneDeregistration(AZUL_KEY key, KeyEvent ke);

};
#endif _Inputable