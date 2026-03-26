#include "AlarmDeregistrationCommand.h"
#include "AlarmableAttorney.h"

AlarmDeregistrationCommand::AlarmDeregistrationCommand(Alarmable* al, AlarmableManager::ALARM_ID i) : alarmable(al), id(i)
{

}

void AlarmDeregistrationCommand::Execute()
{
	AlarmableAttorney::Registration::SceneDeregistration(alarmable, id);
}
