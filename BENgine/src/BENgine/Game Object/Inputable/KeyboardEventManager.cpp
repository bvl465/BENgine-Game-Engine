#include "KeyboardEventManager.h"
#include "Inputable.h"
#include "InputableAttorney.h"
#include "SingleKeyEventManager.h"

#include "../../BENgine.h"

KeyboardEventManager::~KeyboardEventManager()
{
	KeyboardManagerMap::iterator itEnd = keyboardManagerMap.end();
	for (KeyboardManagerMap::iterator it = keyboardManagerMap.begin(); it != itEnd; ++it) {
		delete it->second;
	}
	keyboardManagerMap.clear();
}

void KeyboardEventManager::ProcessKeyboardEvents()
{
	for (KeyboardManagerMap::iterator it = keyboardManagerMap.begin(); it != keyboardManagerMap.end(); it++) {
		it->second->ProcessInputs();
	}
	//float tempTime = BENgine::GetTime();
	//TimelineMap::iterator it = timeline.begin();
	//int i = 0;
	//int s = timeline.size();
	//while (timeline.empty() == false && (*it).first <= tempTime) {
	//	InputableAttorney::GameLoop::TriggerInput((*it).second.first, (*it).second.second);
	//	timeline.erase(it);
	//	it = timeline.begin();
	//	i += 1;
	//
	//}
	//DebugMsg::out("Processed %d alarms out of %d\n", i, s);
}

void KeyboardEventManager::Register(Inputable* in, AZUL_KEY k, KeyEvent ke)
{
	KeyboardManagerMap::iterator it = keyboardManagerMap.find(k);
	if (it == keyboardManagerMap.end()) {
		SingleKeyEventManager* skem = new SingleKeyEventManager(k);
		keyboardManagerMap.insert(std::pair< AZUL_KEY, SingleKeyEventManager*>(k, skem));
		skem->Register(in, ke);
	}
	else {
		it->second->Register(in, ke);
	}
	
}

void KeyboardEventManager::Deregister(Inputable* in, AZUL_KEY k, KeyEvent ke)
{
	KeyboardManagerMap::iterator it = keyboardManagerMap.find(k);
	assert(it != keyboardManagerMap.end());
	it->second->Deregister(in, ke);
}

//void KeyboardEventManager::Register(Inputable* al, ALARM_ID id, float time)
//{
//
//	//InputRegistrationCommandAttorney::Time::
//
//	//InputableAttorney::GameLoop::SetStorageEntryRef(al, id, timeline.insert(std::pair<float, InputEvent>(time + BENgine::GetTime(), InputEvent(al, id))));
//}
//
//void KeyboardEventManager::Deregister(Inputable* al, ALARM_ID id) //easier to debug when a drawable is passed as opposed to its storageEntryRef
//{
//	//timeline.erase(InputableAttorney::GameLoop::GetStorageEntryRef(al, id));
//}
