#include "BENgineSpriteAnimationCommand.h"
#include "BENgineAnimatedSprite.h"


void BENgineSpriteAnimationCommand::Execute()
{
	animatedSprite->SetFrame(ptrGOSprite);
	inTimer = false;
}

void BENgineSpriteAnimationCommand::AddToTimer(GraphicsObject_Sprite* sprite, float time)
{
	ptrGOSprite = sprite;
	if (inTimer == false)
	{
		timer->Register(this, time);
		inTimer = true;
	}
}

void BENgineSpriteAnimationCommand::AddToTimer(float time)
{
	if (inTimer == false)
	{
		timer->Register(this, time);
		inTimer = true;
	}
}

BENgineSpriteAnimationCommand::BENgineSpriteAnimationCommand(BENgineAnimatedSprite* sprite, BENgineSpriteAnimationTimer* animationTimer) : ptrGOSprite(nullptr), animatedSprite(sprite), timer(animationTimer)
{

}

void BENgineSpriteAnimationCommand::SetFrame(GraphicsObject_Sprite* sprite)
{
	ptrGOSprite = sprite;
}

void BENgineSpriteAnimationCommand::SetStorageEntryRef(BENgineSpriteAnimationTimer::StorageEntryRef entryRef)
{
	storageEntryRef = entryRef;
}

void BENgineSpriteAnimationCommand::RemoveFromTimer()
{
	if (inTimer == true)
	{
		timer->Deregister(this->storageEntryRef);
		inTimer = false;
	}

	else
	{
		//assert("Storage entry ref is null");
	}
}
