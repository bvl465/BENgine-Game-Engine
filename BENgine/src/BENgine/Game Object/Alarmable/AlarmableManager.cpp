#include "AlarmableManager.h"
#include "Alarmable.h"
#include "AlarmableAttorney.h"
#include "../../Time/TimeManager.h"
#include "../../BENgine.h"

void AlarmableManager::ProcessAlarms()
{
	//Put tempTime here to avoid calls to the TimeManager for each alarm in the timeline
	const float tempTime = TimeManager::GetTime();

	TimelineMap::iterator it = timeline.begin();

	//Only iterate until it reaches an alarm that is set for a time in the future.
	while (timeline.empty() == false && it->first <= tempTime) {
		AlarmableAttorney::GameLoop::TriggerAlarm((it)->second.first, (it)->second.second);
		timeline.erase(it);
		it = timeline.begin();
	}
}

void AlarmableManager::Register(Alarmable* al, ALARM_ID id, float time)
{
		AlarmableAttorney::GameLoop::SetStorageEntryRef(al, id, timeline.insert(std::pair<float, AlarmEvent>(time + TimeManager::GetTime(), AlarmEvent(al, id))));
}

void AlarmableManager::Deregister(Alarmable* al, ALARM_ID id) //easier to debug when a drawable is passed as opposed to its storageEntryRef
{
	timeline.erase(AlarmableAttorney::GameLoop::GetStorageEntryRef(al, id));
}
