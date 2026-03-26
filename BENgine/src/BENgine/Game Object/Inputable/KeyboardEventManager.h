//Ben La Monica
#pragma once
#ifndef _KeyboardEventManager
#define _KeyboardEventManager
#include <map>
#include "KeyEvent.h"

#include "AzulCore.h"
class SingleKeyEventManager;
class Inputable;
class KeyboardEventManager
{
private:
	using KeyboardManagerMap = std::multimap<AZUL_KEY, SingleKeyEventManager*>;
	KeyboardManagerMap keyboardManagerMap;
public:
	KeyboardEventManager() = default;
	KeyboardEventManager(const KeyboardEventManager&) = delete;
	KeyboardEventManager& operator=(const KeyboardEventManager&) = delete;
	~KeyboardEventManager();

	

	void ProcessKeyboardEvents();
	void Register(Inputable* in, AZUL_KEY k, KeyEvent ke); //add to storageList
	void Deregister(Inputable* in, AZUL_KEY k, KeyEvent ke); //remove from storageList


	//used in registration data in alarmable AND by the user to specify the alarm


	






};
#endif _KeyboardEventManager