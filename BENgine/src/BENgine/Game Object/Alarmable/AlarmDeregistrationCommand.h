//Ben La Monica
#pragma once
#ifndef _AlarmDeregistrationCommand
#define _AlarmDeregistrationCommand
#include "../../Patterns/CommandBase.h"
#include "Alarmable.h"
class Alarmable;
class AlarmDeregistrationCommand : public CommandBase
{
public:
	AlarmDeregistrationCommand() = delete;
	AlarmDeregistrationCommand(const AlarmDeregistrationCommand&) = delete;
	AlarmDeregistrationCommand& operator=(const AlarmDeregistrationCommand&) = delete;
	~AlarmDeregistrationCommand() = default;


	AlarmDeregistrationCommand(Alarmable* al, AlarmableManager::ALARM_ID i);

	//Removes the Alarmable with the id specified from the AlarmableManager timeline so it will not be triggered.
	virtual void Execute() override;
	
private:

	//The Alarmable to deregister from the AlarmableManager.
	Alarmable* alarmable;

	//The id of the alarm to deregister.
	AlarmableManager::ALARM_ID id;

};
#endif _AlarmDeregistrationCommand