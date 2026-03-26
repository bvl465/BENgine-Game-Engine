//Ben La Monica
#pragma once
#ifndef _AlarmableAttorney
#define _AlarmableAttorney

#include "Alarmable.h"

class AlarmableAttorney
{
public:
	class GameLoop
	{
	private:
		friend class AlarmableManager;
		static void TriggerAlarm(Alarmable* al, AlarmableManager::ALARM_ID id) { al->TriggerAlarm(id); }
		static AlarmableManager::StorageEntryRef GetStorageEntryRef(Alarmable* al, AlarmableManager::ALARM_ID id) { return al->GetStorageEntryRef(id); }
		static void SetStorageEntryRef(Alarmable* al, AlarmableManager::ALARM_ID id, AlarmableManager::StorageEntryRef entryRef) { al->SetStorageEntryRef(id, entryRef); }
	};

public:
	class Registration
	{

		friend class AlarmRegistrationCommand;
		friend class AlarmDeregistrationCommand;

	private:
		static void SceneRegistration(Alarmable* al, AlarmableManager::ALARM_ID id, float time) { al->SceneRegistration(id, time); }
		static void SceneDeregistration(Alarmable* al, AlarmableManager::ALARM_ID id) { al->SceneDeregistration(id); }
	};
};
#endif _AlarmableAttorney