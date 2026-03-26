//Ben La Monica
#pragma once
#ifndef _InputableAttorney
#define _InputableAttorney

#include "Inputable.h"

class InputableAttorney
{
public:
	class GameLoop
	{
	private:
		friend class SingleKeyEventManager;
		static SingleKeyEventManager::StorageEntryRef GetStorageEntryRef(Inputable* in, AZUL_KEY k, KeyEvent ke) { return in->GetStorageEntryRef(k, ke); }
		static void SetStorageEntryRef(Inputable* in, AZUL_KEY k, KeyEvent ke, SingleKeyEventManager::StorageEntryRef entryRef) { in->SetStorageEntryRef(k, ke, entryRef); }
		static void KeyPressed(Inputable* in, AZUL_KEY k) { in->KeyPress(k); }
		static void KeyReleased(Inputable* in, AZUL_KEY k) { in->KeyRelease(k); }
		static void KeyIsUp(Inputable* in, AZUL_KEY k) { in->KeyUp(k); }
		static void KeyIsDown(Inputable* in, AZUL_KEY k) { in->KeyDown(k); }
	};

public:
	class Registration
	{
		friend class InputRegistrationCommand;
		friend class InputDeregistrationCommand;

	private:
		static void SceneRegistration(Inputable* in, AZUL_KEY k, KeyEvent ke) { in->SceneRegistration(k, ke); }
		static void SceneDeregistration(Inputable* in, AZUL_KEY k, KeyEvent ke) { in->SceneDeregistration(k, ke); }
	};
};
#endif _InputableAttorney