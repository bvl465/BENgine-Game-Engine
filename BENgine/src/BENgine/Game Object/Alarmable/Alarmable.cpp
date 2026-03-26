#include "../../Scene/SceneManager.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneAttorney.h"
#include "AlarmRegistrationCommand.h"
#include "AlarmDeregistrationCommand.h"
#include "AlarmRegistrationCommandAttorney.h"
#include "Alarmable.h"

Alarmable::Alarmable()
{
	for (int i = 0; i < AlarmableManager::ALARM_NUMBER; i++) {
		RegData[i].curRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
		RegData[i].registrationCmd = new AlarmRegistrationCommand(this, static_cast<AlarmableManager::ALARM_ID>(i));
		RegData[i].deregistrationCmd = new AlarmDeregistrationCommand(this, static_cast<AlarmableManager::ALARM_ID>(i));
	}
	//ALL X-ABLES START OFF DEREGISTERED
}

Alarmable::~Alarmable()
{
	//MORE NEEDS TO BE DONE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	for (int i = 0; i < AlarmableManager::ALARM_NUMBER; i++) {
		RegData[i].curRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
		delete RegData[i].registrationCmd;
		delete RegData[i].deregistrationCmd;
	}

	//Maybe add another enum here to specify it is being deleted
	//This would mean the RegistrationState enum has information
	//that isn't about registration.
}

void Alarmable::SubmitAlarmRegistration(AlarmableManager::ALARM_ID id, float duration)
{
	assert(RegData[int(id)].curRegistrationState == RegistrationState::CURRENTLY_DEREGISTERED);
	AlarmRegistrationCommandAttorney::Time::SetTime(RegData[int(id)].registrationCmd, duration);
	SceneAttorney::Alarm::SubmitCommand(SceneManager::GetCurrentScene(), RegData[int(id)].registrationCmd);
	RegData[int(id)].curRegistrationState = RegistrationState::PENDING_REGISTRATION;
}

void Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_ID id)
{
	assert(RegData[int(id)].curRegistrationState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::Alarm::SubmitCommand(SceneManager::GetCurrentScene(), RegData[int(id)].deregistrationCmd);
	RegData[int(id)].curRegistrationState = RegistrationState::PENDING_DEREGISTRATION;
}

void Alarmable::TriggerAlarm(AlarmableManager::ALARM_ID id)
{
	assert(RegData[int(id)].curRegistrationState == RegistrationState::CURRENTLY_REGISTERED);
	switch (id) {
	case AlarmableManager::ALARM_ID::ALARM_0:
		this->Alarm0();
		break;
	case AlarmableManager::ALARM_ID::ALARM_1:
		this->Alarm1();
		break;
	case AlarmableManager::ALARM_ID::ALARM_2:
		this->Alarm2();
		break;
	};
	RegData[int(id)].curRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Alarmable::Alarm0()
{
}

void Alarmable::Alarm1()
{
}

void Alarmable::Alarm2()
{
}

void Alarmable::SetStorageEntryRef(AlarmableManager::ALARM_ID id, AlarmableManager::StorageEntryRef entryRef)
{
	RegData[int(id)].storageEntryRef = entryRef;
}

AlarmableManager::StorageEntryRef Alarmable::GetStorageEntryRef(AlarmableManager::ALARM_ID id)
{
	return RegData[int(id)].storageEntryRef;
}

void Alarmable::SceneRegistration(AlarmableManager::ALARM_ID id, float time)
{
	assert(RegData[int(id)].curRegistrationState == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::Alarm::Register(SceneManager::GetCurrentScene(), this, id, time);
	RegData[int(id)].curRegistrationState = RegistrationState::CURRENTLY_REGISTERED;
}

void Alarmable::SceneDeregistration(AlarmableManager::ALARM_ID id)
{
	assert(RegData[int(id)].curRegistrationState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::Alarm::Deregister(SceneManager::GetCurrentScene(), this, id);
	RegData[int(id)].curRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
}
