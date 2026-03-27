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
class SceneSwitchingDemo;

class FlightScene : public Scene
{
public:
	FlightScene() = default;
	FlightScene(const FlightScene&) = delete;
	FlightScene& operator=(const FlightScene&) = delete;
	~FlightScene();
	

private:
	
	FirstPersonFlightCam* flightCam = nullptr;
	
	Cockpit* cockpit = nullptr;

	SceneSwitchingDemo* sceneSwitcher = nullptr;
	virtual void Initialize() override;
	virtual void SceneEnd() override;

};
#endif _FlightScene