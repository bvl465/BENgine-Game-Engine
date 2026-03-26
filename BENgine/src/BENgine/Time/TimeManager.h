//Ben La Monica
#pragma once
#ifndef _TimeManager
#define _TimeManager

class FreezeTime;
class TimeManager
{
public:
	friend class TimeManagerAttorney;

	//Returns the current time in seconds since the TimeManager was initialized.
	static float GetTime();

	//Returns time since the previous frame in seconds
	static float GetFrameTime();

private:

	TimeManager();
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;
	~TimeManager() = default;
	static TimeManager& Instance(); // Access reference (all public methods will be static)


	static void Delete(); //MUST be called by attorney and NO ONE ELSE

	
	float privGetFrameTime() const;

	static void ProcessTime();
	void privProcessTime();
	
	float privGetTime() const;

	static TimeManager* ptrInstance;
	float curTime = 0.f;
	float prevTime = 0.f;
	float frameTime = 0.f;

	FreezeTime* FrzTime;
};
#endif _TimeManager