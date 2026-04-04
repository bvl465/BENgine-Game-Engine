#pragma once
#ifndef _Cockpit
#define _Cockpit
#include "../src/BENgine/Game Object/GameObject.h"
class BENgineSprite;
class BENgineSpriteCollection;
class BENgineAnimatedSprite;
class BENgineSpriteAnimation;
class Cockpit : public GameObject
{
public:
	Cockpit();
	Cockpit(const Cockpit&) = delete;
	Cockpit& operator=(const Cockpit&) = delete;
	~Cockpit();
	virtual void KeyPress(AZUL_KEY k);
	virtual void KeyDown(AZUL_KEY k);
	virtual void KeyRelease(AZUL_KEY k);

private:
	BENgineSprite* reticle;
	BENgineAnimatedSprite* cockpitSprite;
	BENgineSpriteAnimation* cockpitRedAnimation;
	BENgineSpriteAnimation* cockpitDamage;
	BENgineAnimatedSprite* gameCubeSprite;
	BENgineSpriteAnimation* gameCubeRedAnimation;
	BENgineSpriteCollection* spriteCollection1;
	float posX;
	float posY;
	float gameCubeAngle = 0.f;
};
#endif _Cockpit