//Ben La Monica
#pragma once
#ifndef _FlightScene
#define _FlightScene
#include "../src/BENgine/Scene/Scene.h"
class FreeCamera;
class WorldPlane;
class Axis;
class Enemy;
class Frigate;
class SpriteCollectionDemo;
class FirstPersonFlightCam;
class Cockpit;

class FlightScene : public Scene
{
public:
	FlightScene() = default;
	FlightScene(const FlightScene&) = delete;
	FlightScene& operator=(const FlightScene&) = delete;
	~FlightScene();
	

private:
	
	FirstPersonFlightCam* flightCam = nullptr;
	
	Frigate* frigate = nullptr;
	
	Enemy* enemy = nullptr;
	Enemy* enemy2 = nullptr;
	
	Axis* axis = nullptr;
	Cockpit* cockpit = nullptr;

	SpriteCollectionDemo* spriteCollectionDemo = nullptr;
	virtual void Initialize() override;
	virtual void SceneEnd() override;

};
#endif _FlightScene