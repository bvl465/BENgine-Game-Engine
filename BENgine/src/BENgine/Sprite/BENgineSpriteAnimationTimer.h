//Ben La Monica
#pragma once
#ifndef _BENgineSpriteAnimationTimer
#define _BENgineSpriteAnimationTimer
#include <map>
#include <list>
class BENgineSpriteAnimationCommandBase;

class BENgineSpriteAnimationTimer
{
public:

private:


	using TimelineMap = std::multimap<float, BENgineSpriteAnimationCommandBase*>;
	using PendingTimerList = std::list<std::pair<float, BENgineSpriteAnimationCommandBase*>>;
	TimelineMap timeline;
	PendingTimerList pendingTimerList;



public:

	BENgineSpriteAnimationTimer() = default;
	BENgineSpriteAnimationTimer(const BENgineSpriteAnimationTimer&) = delete;
	BENgineSpriteAnimationTimer& operator=(const BENgineSpriteAnimationTimer&) = delete;
	~BENgineSpriteAnimationTimer() = default;

	using TimeLineMapStorageEntryRef = TimelineMap::iterator;
	using PendingTimerListStorageEntryRef = PendingTimerList::iterator;
	void ProcessAnimations();
	void AddPendingAnimations();
	

	void Register(BENgineSpriteAnimationCommandBase* cmd, float time); //add to storageList
	void Deregister(TimeLineMapStorageEntryRef entryRef); //remove from storageList
	void Deregister(PendingTimerListStorageEntryRef entryRef);

};
#endif _BENgineSpriteAnimationTimer