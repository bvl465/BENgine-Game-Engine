//Ben La Monica
#pragma once
#ifndef _AlarmRegistrationCommandAttorney
#define _AlarmRegistrationCommandAttorney

#include "AlarmRegistrationCommand.h"

class AlarmRegistrationCommandAttorney
{
public:
	class Time
	{
		friend class Alarmable;
	private:

		//Sets the time that the alarm should be triggered after.
		//Parameters:
		//arc - the AlarmRegistrationCommand to set the time of.
		//t - the time in seconds until the alarm should be triggered.
		static void SetTime(AlarmRegistrationCommand* arc, float t) { arc->SetTime(t); }
		
	};
};
#endif _AlarmRegistrationCommandAttorney