#include "TimeManager.h"
#include "FreezeTime.h"
TimeManager* TimeManager::ptrInstance = nullptr;

TimeManager::TimeManager() {
	FrzTime = new FreezeTime();
}

float TimeManager::GetTime()
{
	return Instance().privGetTime();
}

float TimeManager::GetFrameTime()
{
	return Instance().privGetFrameTime();
}

TimeManager& TimeManager::Instance() //Singelton set up
{
	if (ptrInstance == nullptr) {
		ptrInstance = new TimeManager();
	}
	return *ptrInstance;
}

void TimeManager::Delete()
{
	if (ptrInstance != nullptr) {
		delete ptrInstance->FrzTime;
		delete ptrInstance;
		ptrInstance = nullptr;
	}
}

float TimeManager::privGetFrameTime() const
{
	return frameTime;
}

void TimeManager::ProcessTime()
{
	Instance().privProcessTime();
}

void TimeManager::privProcessTime()
{
	prevTime = curTime;
	curTime = FrzTime->ComputeGameTime(prevTime);
	frameTime = curTime - prevTime;
	
}

float TimeManager::privGetTime() const
{
	return curTime;
}
