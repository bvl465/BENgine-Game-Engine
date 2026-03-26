#include "AlarmRegistrationCommand.h"
#include "AlarmableAttorney.h"


AlarmRegistrationCommand::AlarmRegistrationCommand(Alarmable* al, AlarmableManager::ALARM_ID i) : alarmable(al), id(i)
{

}

void AlarmRegistrationCommand::Execute()
{
	AlarmableAttorney::Registration::SceneRegistration(alarmable, id, time);
}

void AlarmRegistrationCommand::SetTime(float t)
{
	time = t;
}
