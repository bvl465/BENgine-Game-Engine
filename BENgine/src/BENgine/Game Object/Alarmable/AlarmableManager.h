//Ben La Monica
#pragma once
#ifndef _AlarmableManager
#define _AlarmableManager
#include <map>
class Alarmable;
class AlarmableManager
{
public:

	enum class ALARM_ID {
		//Alarm0()
		ALARM_0,
		//Alarm1()
		ALARM_1,
		//Alarm2()
		ALARM_2
	};

	//Number of alarms that an Alarmable can have.
	static const int ALARM_NUMBER = 3;

private:

	using AlarmEvent = std::pair<Alarmable*, ALARM_ID>;
	using TimelineMap = std::multimap<float, AlarmEvent>;
	TimelineMap timeline;

public:

	AlarmableManager() = default;
	AlarmableManager(const AlarmableManager&) = delete;
	AlarmableManager& operator=(const AlarmableManager&) = delete;
	~AlarmableManager() = default;

	//Location of the alarm in the timeline.
	using StorageEntryRef = TimelineMap::iterator;

	//Triggers alarms after the time they were set for has passed and then removes them from the timeline.
	void ProcessAlarms();

	//Adds the passed Alarmable to the timeline with the time it should be triggered at and the id of the alarm to trigger.
	//Parameters:
	//al - the Alarmable to register
	//id - the id of the alarm to trigger after the time has passed
	//time - the time in seconds until the alarm should be triggered
	void Register(Alarmable* al, ALARM_ID id, float time);

	//Removes the passed Alarmable with the corresponding id from the timeline so it will not be triggered.
	//Parameters:
	//al - the Alarmable to deregister if the id of the alarm to deregister matches the id passed
	//id - the id of the alarm to deregister
	void Deregister(Alarmable* al, ALARM_ID id);
};
#endif _AlarmableManager