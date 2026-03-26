//Ben La Monica
#pragma once
#ifndef _BENgineSpriteAnimationCommandBase
#define _BENgineSpriteAnimationCommandBase
#include "AzulCore.h"
#include "BENgineSpriteAnimationTimer.h"
class BENgineAnimatedSprite;
class BENgineSpriteAnimationCommandBase
{
public:
	BENgineSpriteAnimationCommandBase();
	BENgineSpriteAnimationCommandBase(const BENgineSpriteAnimationCommandBase&) = delete;
	BENgineSpriteAnimationCommandBase& operator=(const BENgineSpriteAnimationCommandBase&) = delete;
	virtual ~BENgineSpriteAnimationCommandBase();

	//BENgineSpriteAnimationCommandBase(BENgineAnimatedSprite* sprite, BENgineSpriteAnimationTimer* animationTimer);

	virtual void Execute() = 0;
	void AddToTimer(GraphicsObject_Sprite* sprite, float time);
	void AddToTimer(float time);
	virtual void SetFrame(GraphicsObject_Sprite* sprite);

	//Make an attorney

	void RemoveFromTimer();
	enum TimerLocation {
		IN_TIMER,
		PENDING_TIMER,
		NOT_IN_TIMER
	};
	TimerLocation GetTimerLocation() const;

protected:
	BENgineAnimatedSprite* animatedSprite;
	GraphicsObject_Sprite* ptrGOSprite;

private:

	friend class BENgineSpriteAnimationCommandBaseAttorney;

	//Don't want the user to change this in derived commands.
	void TriggerExecute();
	void SetTimelineStorageEntryRef(BENgineSpriteAnimationTimer::TimeLineMapStorageEntryRef entryRef);
	void SetPendingStorageEntryRef(BENgineSpriteAnimationTimer::PendingTimerListStorageEntryRef entryRef);

	TimerLocation timerLocation;
	BENgineSpriteAnimationTimer::TimeLineMapStorageEntryRef timeLineStorageEntryRef;
	BENgineSpriteAnimationTimer::PendingTimerListStorageEntryRef pendingTimerStorageEntryRef;

};
#endif _BENgineSpriteAnimationCommandBase