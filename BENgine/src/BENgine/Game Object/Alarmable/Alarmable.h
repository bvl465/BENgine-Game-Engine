//Ben La Monica
#pragma once
#ifndef _Alarmable
#define _Alarmable
#include "../RegistrationState.h"
#include "AlarmableManager.h"
class AlarmRegistrationCommand;
class AlarmDeregistrationCommand;
class Alarmable
{
public:
	Alarmable();
	Alarmable(const Alarmable&) = delete;
	Alarmable& operator=(const Alarmable&) = delete;
	virtual ~Alarmable();

protected:

	//Submits an AlarmRegistrationCommand to the SceneRegistrationBroker to have the Alarmable added to the AlarmableManager's timeline which will trigger the alarm with the corresponding id after the specified time has passed.
	//Parameters:
	//id: the id of the alarm to register
	//duration: the time in seconds until the alarm should be triggered
	void SubmitAlarmRegistration(AlarmableManager::ALARM_ID id, float duration);

	//Submits an AlarmDeregistrationCommand to the SceneRegistrationBroker to have the Alarmable with the corresponding id removed from the AlarmableManager's timeline so as to not be triggered.
	//Parameters:
	//id: the id of the alarm to deregister
	void SubmitAlarmDeregistration(AlarmableManager::ALARM_ID id);

private:

	friend class AlarmableAttorney;

	//Triggers the alarm that corresponds with the id passed and then sets the registration state of that alarm to deregistered.
	//Parameters:
	//id: the id of the alarm to trigger
	void TriggerAlarm(AlarmableManager::ALARM_ID id);

	//To be implemented by user
	virtual void Alarm0();

	//To be implemented by user
	virtual void Alarm1();

	//To be implemented by user
	virtual void Alarm2();

	struct RegistrationData {
		AlarmRegistrationCommand* registrationCmd = nullptr;
		AlarmDeregistrationCommand* deregistrationCmd = nullptr;
		AlarmableManager::StorageEntryRef storageEntryRef;
		RegistrationState curRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
	};

	//Array of registration data for each alarm
	RegistrationData RegData[AlarmableManager::ALARM_NUMBER];

	//Used by the AlarmableManager to set the StorageEntryRef of the alarm that corresponds with the id passed when it is added to the timeline.
	//Parameters:
	//id: the id of the alarm to set the StorageEntryRef of
	//entryRef: the StorageEntryRef to set the alarm's storageEntryRef to
	void SetStorageEntryRef(AlarmableManager::ALARM_ID id, AlarmableManager::StorageEntryRef entryRef);

	//Returns the StorageEntryRef of the alarm that corresponds with the id passed, which is used by the AlarmableManager to
	//find and remove the alarm from its timeline when it is deregistered.
	//Parameters:
	//id: the id of the alarm to get the StorageEntryRef of
	AlarmableManager::StorageEntryRef GetStorageEntryRef(AlarmableManager::ALARM_ID id);

	//Has the current Scene add the Alarmable to the AlarmableManager's timeline which will trigger the 
	//alarm with the ALARM_ID after the specified time has passed.
	//Parameters:
	//id - the id of the alarm to set
	//time - the time in seconds until the alarm should be triggered
	virtual void SceneRegistration(AlarmableManager::ALARM_ID id, float time);

	//Has the current Scene remove the Alarmable from the AlarmableManager's timeline to stop the alarm with the ALARM_ID from being triggered.
	//Parameters:
	//id - the id of the alarm to deregister
	virtual void SceneDeregistration(AlarmableManager::ALARM_ID id);



};
#endif _Alarmable