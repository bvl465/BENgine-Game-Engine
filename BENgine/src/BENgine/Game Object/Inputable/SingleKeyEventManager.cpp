#include "SingleKeyEventManager.h"
#include "Inputable.h"
#include "InputableAttorney.h"
#include "../../BENgine.h"

SingleKeyEventManager::SingleKeyEventManager(AZUL_KEY k) : key(k)
{
	if (Keyboard::GetKeyState(k) == true) {
		prevKeyState = KeyEvent::KEY_PRESSED;
	}
	else {
		prevKeyState = KeyEvent::KEY_UP;
	}
}

void SingleKeyEventManager::ProcessInputs()
{
	//Maybe replace with an FSM

	if (Keyboard::GetKeyState(key) == false) {
		if (prevKeyState == KeyEvent::KEY_UP || prevKeyState == KeyEvent::KEY_RELEASED) {
			prevKeyState = KeyEvent::KEY_UP;
			for each (Inputable * inputable in upList) {
				InputableAttorney::GameLoop::KeyIsUp(inputable, key);
			}
		}
		else {
			prevKeyState = KeyEvent::KEY_RELEASED;
			for each (Inputable* inputable in releaseList) {
				InputableAttorney::GameLoop::KeyReleased(inputable, key);
			}
		}
	}
	else if (prevKeyState == KeyEvent::KEY_DOWN || prevKeyState == KeyEvent::KEY_PRESSED) {
		
		prevKeyState = KeyEvent::KEY_DOWN;
		for each (Inputable * inputable in downList) {
			InputableAttorney::GameLoop::KeyIsDown(inputable, key);
		}
	}
	else {
		prevKeyState = KeyEvent::KEY_PRESSED;
		for each (Inputable * inputable in pressList) {
			InputableAttorney::GameLoop::KeyPressed(inputable, key);
		}
	}
}

void SingleKeyEventManager::Register(Inputable* in, KeyEvent ke)
{
	switch (ke) {
	case KeyEvent::KEY_PRESSED:
		InputableAttorney::GameLoop::SetStorageEntryRef(in, key, ke, pressList.insert(pressList.end(), in));
		break;
	case KeyEvent::KEY_RELEASED:
		InputableAttorney::GameLoop::SetStorageEntryRef(in, key, ke, releaseList.insert(releaseList.end(), in));
		break;
	case KeyEvent::KEY_DOWN:
		InputableAttorney::GameLoop::SetStorageEntryRef(in, key, ke, downList.insert(downList.end(), in));
		break;
	case KeyEvent::KEY_UP:
		InputableAttorney::GameLoop::SetStorageEntryRef(in, key, ke, upList.insert(upList.end(), in));
		break;
	}
}

void SingleKeyEventManager::Deregister(Inputable* in, KeyEvent ke)
{
	switch (ke) {
	case KeyEvent::KEY_PRESSED:
		pressList.erase(InputableAttorney::GameLoop::GetStorageEntryRef(in, key, ke));
		break;
	case KeyEvent::KEY_RELEASED:
		releaseList.erase(InputableAttorney::GameLoop::GetStorageEntryRef(in, key, ke));
		break;
	case KeyEvent::KEY_DOWN:
		downList.erase(InputableAttorney::GameLoop::GetStorageEntryRef(in, key, ke));
		break;
	case KeyEvent::KEY_UP:
		upList.erase(InputableAttorney::GameLoop::GetStorageEntryRef(in, key, ke));
		break;
	}
}