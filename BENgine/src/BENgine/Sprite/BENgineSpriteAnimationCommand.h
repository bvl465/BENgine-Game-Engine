//Ben La Monica
#pragma once
#ifndef _BENgineSpriteAnimationCommand
#define _BENgineSpriteAnimationCommand
#include "AzulCore.h"
#include "BENgineSpriteAnimationTimer.h"
class BENgineAnimatedSprite;
class BENgineSpriteAnimationCommand
{
public:
	BENgineSpriteAnimationCommand() = delete;
	BENgineSpriteAnimationCommand(const BENgineSpriteAnimationCommand&) = delete;
	BENgineSpriteAnimationCommand& operator=(const BENgineSpriteAnimationCommand&) = delete;
	~BENgineSpriteAnimationCommand() = default;


	BENgineSpriteAnimationCommand(BENgineAnimatedSprite* sprite, BENgineSpriteAnimationTimer* animationTimer);

	void Execute();
	void AddToTimer(GraphicsObject_Sprite* sprite, float time);
	void AddToTimer(float time);
	void SetFrame(GraphicsObject_Sprite* sprite);
	void SetStorageEntryRef(BENgineSpriteAnimationTimer::StorageEntryRef entryRef);
	void RemoveFromTimer();
	//what would this being const do?
	//virtual void Execute() const override;
	
private:
	BENgineSpriteAnimationTimer::StorageEntryRef storageEntryRef;
	BENgineAnimatedSprite* animatedSprite;
	GraphicsObject_Sprite* ptrGOSprite;
	BENgineSpriteAnimationTimer* timer;
	bool inTimer = false;

};
#endif _BENgineSpriteAnimationCommand