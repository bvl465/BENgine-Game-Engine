#include "BENgineSpriteAnimationTimer.h"
#include "BENgineSpriteAnimationCommandBase.h"
#include "../Time/TimeManager.h"
#include "BENgineSpriteAnimationCommandBaseAttorney.h"


void BENgineSpriteAnimationTimer::ProcessAnimations()
{
	float tempTime = TimeManager::GetTime();
	TimelineMap::iterator it = timeline.begin();
	//int i = 0;
	//int s = timeline.size();
	while (timeline.empty() == false && (*it).first <= tempTime) {
		BENgineSpriteAnimationCommandBaseAttorney::Timer::TriggerExecute(it->second);
		//it->second->TriggerExecute();
		timeline.erase(it);
		it = timeline.begin();
		//i += 1;

	}
	//DebugMsg::out("Processed %d alarms out of %d\n", i, s);
}

void BENgineSpriteAnimationTimer::AddPendingAnimations()
{
	while (pendingTimerList.empty() == false) {
		BENgineSpriteAnimationCommandBase* cmd = ((pendingTimerList.front()).second);
		BENgineSpriteAnimationCommandBaseAttorney::Timer::SetTimelineStorageEntryRef(cmd, timeline.insert(std::pair<float, BENgineSpriteAnimationCommandBase*>((pendingTimerList.front()).first, cmd)));
		//cmd->SetTimelineStorageEntryRef(timeline.insert(std::pair<float, BENgineSpriteAnimationCommandBase*>((pendingTimerList.front()).first, cmd)));
		pendingTimerList.pop_front();
	}

}

void BENgineSpriteAnimationTimer::Register(BENgineSpriteAnimationCommandBase* cmd, float time)
{

	
	BENgineSpriteAnimationCommandBaseAttorney::Timer::SetPendingStorageEntryRef(cmd, pendingTimerList.insert(pendingTimerList.begin(), std::pair<float, BENgineSpriteAnimationCommandBase*>(time + TimeManager::GetTime(), cmd)));
	//cmd->SetPendingStorageEntryRef(pendingTimerList.insert(pendingTimerList.begin(), std::pair<float, BENgineSpriteAnimationCommandBase*>(time + TimeManager::GetTime(), cmd)));
}

void BENgineSpriteAnimationTimer::Deregister(TimeLineMapStorageEntryRef storageEntryRef) //easier to debug when a drawable is passed as opposed to its storageEntryRef
{
	timeline.erase(storageEntryRef);
}

void BENgineSpriteAnimationTimer::Deregister(PendingTimerListStorageEntryRef storageEntryRef) //easier to debug when a drawable is passed as opposed to its storageEntryRef
{
	pendingTimerList.erase(storageEntryRef);
}
