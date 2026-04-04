#pragma once
#ifndef _SpriteCollectionDemo
#define _SpriteCollectionDemo
#include "../src/BENgine/Game Object/GameObject.h"
class BENgineSprite;
class BENgineSpriteCollection;
class BENgineAnimatedSprite;
class BENgineSpriteAnimation;
class SpriteCollectionDemo : public GameObject
{
public:
	SpriteCollectionDemo();
	SpriteCollectionDemo(const SpriteCollectionDemo&) = delete;
	SpriteCollectionDemo& operator=(const SpriteCollectionDemo&) = delete;
	~SpriteCollectionDemo();
	virtual void KeyPress(AZUL_KEY k);
	virtual void KeyDown(AZUL_KEY k);

private:

	float animationDurationModifier = 1.f;
	float durationMax = 1.5f;
	float durationMin = .25f;
	float scaleX = 1.f;
	float scaleY = 1.f;
	BENgineSpriteAnimation* animation1;
	BENgineSpriteAnimation* animation11;
	BENgineSpriteAnimation* animation2;
	BENgineSpriteAnimation* animation22;
	BENgineSprite* regularSprite1;
	BENgineSprite* regularSprite2;
	BENgineAnimatedSprite* animatedSprite1;
	BENgineAnimatedSprite* animatedSprite2;
	BENgineSpriteCollection* spriteCollection1;
	BENgineSpriteCollection* spriteCollection2;
	BENgineSpriteCollection* spriteCollection3;

	BENgineSprite* collectionViewer;

	BENgineSprite* testSprite;

};
#endif _SpriteCollectionDemo