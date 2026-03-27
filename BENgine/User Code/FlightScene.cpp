#include "FlightScene.h"
#include "Axis.h"
#include "WorldPlane.h"
#include "Enemy.h"
#include "StitchSprite.h"
#include "Frigate.h"
#include "Bullet.h"
#include "../src/BENgine/Camera/FreeCamera.h"
#include "AnimatedSpriteDemo.h"
#include "SpriteCollectionDemo.h"
#include "Cockpit.h"
#include "../src/BENgine/Scene/SceneManager.h"
#include "FirstPersonFlightCam.h"
#include "SceneSwitchingDemo.h"
//#include "StarFighter.h"
//#include "../src/BENgine/BENgineModels/Terrain/Terrain.h"

FlightScene::~FlightScene()
{

	delete sceneSwitcher;
	delete flightCam;
	delete cockpit;

	
}

void FlightScene::Initialize()
{
	(SceneManager::GetCurrentScene())->GetTerrainManager()->SetCurrentTerrain("pTerrainTest2TerrainObject");
	CreateLayers({ "CockpitHUD", "Layer1", "Layer2", "Layer3" });
	flightCam = new FirstPersonFlightCam();
	SetCurrentCamera(flightCam->GetCamera());

	sceneSwitcher = new SceneSwitchingDemo();

	cockpit = new Cockpit();
}

void FlightScene::SceneEnd()
{

}
