//Ben La Monica
#pragma once
#ifndef _TimeManagerAttorney
#define _TimeManagerAttorney

#include "TimeManager.h"

class TimeManagerAttorney
{
public:
	class Time
	{
	private:
		friend class BENgine;
		static void ProcessTime() { TimeManager::ProcessTime(); }
		static void Delete() { TimeManager::Delete(); }
	};
};
#endif _TimeManagerAttorney