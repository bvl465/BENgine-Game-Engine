#include "BENgineSpriteAnimationCommandBase.h"
#include "BENgineAnimatedSprite.h"
#include "../Scene/SceneAttorney.h"
#include "../Scene/SceneManager.h"


BENgineSpriteAnimationCommandBase::BENgineSpriteAnimationCommandBase() : timerLocation(NOT_IN_TIMER)
{
	animatedSprite = nullptr;
	ptrGOSprite = nullptr;
}

BENgineSpriteAnimationCommandBase::~BENgineSpriteAnimationCommandBase()
{
	if (timerLocation == IN_TIMER)
	{
		SceneAttorney::AnimatedSprite::GetAnimationTimer(SceneManager::GetCurrentScene())->Deregister(timeLineStorageEntryRef);
	}
	else if (timerLocation == PENDING_TIMER)
	{
		SceneAttorney::AnimatedSprite::GetAnimationTimer(SceneManager::GetCurrentScene())->Deregister(pendingTimerStorageEntryRef);
	}
}

void BENgineSpriteAnimationCommandBase::AddToTimer(float time)
{
	if (timerLocation == NOT_IN_TIMER)
	{
		SceneAttorney::AnimatedSprite::GetAnimationTimer(SceneManager::GetCurrentScene())->Register(this, time);
		
	}
}

void BENgineSpriteAnimationCommandBase::TriggerExecute()
{
	timerLocation = NOT_IN_TIMER;
	Execute();
}

void BENgineSpriteAnimationCommandBase::AddToTimer(GraphicsObject_Sprite* sprite, float time)
{

	if (timerLocation == NOT_IN_TIMER)
	{
		this->ptrGOSprite = sprite;
		SceneAttorney::AnimatedSprite::GetAnimationTimer(SceneManager::GetCurrentScene())->Register(this, time);
	}
}

void BENgineSpriteAnimationCommandBase::SetFrame(GraphicsObject_Sprite* sprite)
{
	ptrGOSprite = sprite;
}

void BENgineSpriteAnimationCommandBase::SetTimelineStorageEntryRef(BENgineSpriteAnimationTimer::TimeLineMapStorageEntryRef entryRef)
{
	timeLineStorageEntryRef = entryRef;
	timerLocation = IN_TIMER;
}

void BENgineSpriteAnimationCommandBase::SetPendingStorageEntryRef(BENgineSpriteAnimationTimer::PendingTimerListStorageEntryRef entryRef)
{
	pendingTimerStorageEntryRef = entryRef;
	timerLocation = PENDING_TIMER;

}
void BENgineSpriteAnimationCommandBase::RemoveFromTimer()
{
	if (timerLocation == IN_TIMER)
	{
		SceneAttorney::AnimatedSprite::GetAnimationTimer(SceneManager::GetCurrentScene())->Deregister(timeLineStorageEntryRef);
		timerLocation = NOT_IN_TIMER;
	}
	else if (timerLocation == PENDING_TIMER)
	{
		SceneAttorney::AnimatedSprite::GetAnimationTimer(SceneManager::GetCurrentScene())->Deregister(pendingTimerStorageEntryRef);
		timerLocation = NOT_IN_TIMER;
	}

}

BENgineSpriteAnimationCommandBase::TimerLocation BENgineSpriteAnimationCommandBase::GetTimerLocation() const
{
	return timerLocation;
}
