//Ben La Monica
#pragma once
#ifndef _BENgineSpriteAnimationCommandLoop
#define _BENgineSpriteAnimationCommandLoop
#include "AzulCore.h"
#include "BENgineSpriteAnimationTimer.h"
#include "BENgineSpriteAnimationCommandBase.h"
class BENgineAnimatedSprite;
class BENgineSpriteAnimationCommandLoop : public BENgineSpriteAnimationCommandBase
{
public:
	BENgineSpriteAnimationCommandLoop() = delete;
	BENgineSpriteAnimationCommandLoop(const BENgineSpriteAnimationCommandLoop&) = delete;
	BENgineSpriteAnimationCommandLoop& operator=(const BENgineSpriteAnimationCommandLoop&) = delete;
	~BENgineSpriteAnimationCommandLoop() = default;

	BENgineSpriteAnimationCommandLoop(BENgineAnimatedSprite* sprite);

	void Execute() override;
	//void AddToTimer(GraphicsObject_Sprite* sprite, float time) override;
	//void AddToTimer(float time) override;
	//void SetFrame(GraphicsObject_Sprite* sprite) override;
	//void SetTimelineStorageEntryRef(BENgineSpriteAnimationTimer::TimeLineMapStorageEntryRef entryRef) override;
	//void SetPendingStorageEntryRef(BENgineSpriteAnimationTimer::PendingTimerListStorageEntryRef entryRef) override;
	//void RemoveFromTimer() override;
	
private:
	//BENgineSpriteAnimationTimer::TimeLineMapStorageEntryRef timeLineStorageEntryRef;
	//BENgineSpriteAnimationTimer::PendingTimerListStorageEntryRef pendingTimerStorageEntryRef;
	//BENgineAnimatedSprite* animatedSprite;
	//GraphicsObject_Sprite* ptrGOSprite;
	//BENgineSpriteAnimationTimer* timer;
	//TimerLocation timerLocation;

};
#endif _BENgineSpriteAnimationCommandLoop