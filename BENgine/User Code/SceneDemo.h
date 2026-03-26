//Ben La Monica
#pragma once
#ifndef _SceneDemo
#define _SceneDemo
#include "../src/BENgine/Scene/Scene.h"
class FreeCamera;
class WorldPlane;
class Axis;
class Enemy;
class Frigate;
class StitchSprite;
class AnimatedSpriteDemo;
class SpriteCollectionDemo;
class Terrain;
class FirstPersonFlightCam;
class FreeCamera;

class SceneDemo : public Scene
{
public:
	SceneDemo() = default;
	SceneDemo(const SceneDemo&) = delete;
	SceneDemo& operator=(const SceneDemo&) = delete;
	~SceneDemo();
	//StarFighter* GetStarFighter() const;

	//virtual void Draw() override;
	//virtual void Update() override;

private:

	FreeCamera* freeCam = nullptr;
	
	Frigate* frigate = nullptr;
	//Frigate* frigate2 = nullptr;
	Enemy* enemy = nullptr;
	Enemy* enemy2 = nullptr;

	StitchSprite* stitch = nullptr;

	StitchSprite* stitch2 = nullptr;

	//AnimatedSpriteDemo* animatedsprite = nullptr;
	WorldPlane* plane = nullptr;
	Axis* axis = nullptr;
	//Cockpit* cockpit = nullptr;

	SpriteCollectionDemo* spriteCollectionDemo = nullptr;
	virtual void Initialize() override;
	virtual void SceneEnd() override;

};
#endif _SceneDemo