//Ben La Monica
#pragma once
#ifndef _AlarmRegistrationCommand
#define _AlarmRegistrationCommand
#include "../../Patterns/CommandBase.h"
#include "Alarmable.h"
class Alarmable;
class AlarmRegistrationCommand : public CommandBase
{
public:
	AlarmRegistrationCommand() = delete;
	AlarmRegistrationCommand(const AlarmRegistrationCommand&) = delete;
	AlarmRegistrationCommand& operator=(const AlarmRegistrationCommand&) = delete;
	~AlarmRegistrationCommand() = default;


	AlarmRegistrationCommand(Alarmable* al, AlarmableManager::ALARM_ID i);

	//Adds the Alarmable to the AlarmableManager timeline with the time it should be triggered at and the id of the alarm to trigger after the time has passed.
	virtual void Execute() override;

private:
	friend class AlarmRegistrationCommandAttorney;

	//Sets the time that the alarm should be triggered after.
	//Parameters:
	//t - the time in seconds until the alarm should be triggered
	void SetTime(float t);

	//The Alarmable to register with the AlarmableManager.
	Alarmable* alarmable;

	//The duration of the alarm.
	float time = 0;

	//The id of the alarm to register.
	AlarmableManager::ALARM_ID id;

};
#endif _AlarmRegistrationCommand