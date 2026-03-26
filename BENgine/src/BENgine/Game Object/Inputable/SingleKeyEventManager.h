//Ben La Monica
#pragma once
#ifndef _SingleKeyEventManager
#define _SingleKeyEventManager
#include "KeyEvent.h"
#include <list>
#include "AzulCore.h"
class Inputable;
class SingleKeyEventManager
{
private:

	AZUL_KEY key; //main way in which a single key event manager is identified

	using InputableList = std::list<Inputable*>;

	//lists of inputables tied to be alerted based on their corresponding key event.
	InputableList pressList;
	InputableList releaseList;
	InputableList downList;
	InputableList upList;
	KeyEvent prevKeyState;
	
public:
	SingleKeyEventManager() = delete;
	SingleKeyEventManager(const SingleKeyEventManager&) = delete;
	SingleKeyEventManager& operator=(const SingleKeyEventManager&) = delete;
	~SingleKeyEventManager() = default;
	SingleKeyEventManager(AZUL_KEY k);

	using StorageEntryRef = InputableList::iterator;

	void ProcessInputs(); //notifies inputables
	void Register(Inputable* in, KeyEvent ke); //add to inputable list
	void Deregister(Inputable* in, KeyEvent ke); //remove from the inputable list

};
#endif _InputableManager