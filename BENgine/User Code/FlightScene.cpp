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
//#include "StarFighter.h"
//#include "../src/BENgine/BENgineModels/Terrain/Terrain.h"

FlightScene::~FlightScene()
{

	delete frigate;

	delete axis;
	delete flightCam;
	delete enemy;
	delete enemy2;
	delete cockpit;
	delete spriteCollectionDemo;
	
}

void FlightScene::Initialize()
{
	(SceneManager::GetCurrentScene())->GetTerrainManager()->SetCurrentTerrain("pTerrainTest2TerrainObject");
	//terrain = new Terrain("HMTest16.tga", 400, 100, 0, TextureManager::GetTexture("pHeightMapTest"), 1, 1);
	CreateLayers({ "CockpitHUD", "Layer1", "Layer2", "Layer3" });
	flightCam = new FirstPersonFlightCam();
	SetCurrentCamera(flightCam->GetCamera());

	frigate = new Frigate();

	cockpit = new Cockpit();

	axis = new Axis();
	enemy = new Enemy();
	enemy2 = new Enemy();
	enemy2->SetWorld(Matrix(SCALE, 1.f, 1.f, 1.f) * Matrix(ROT_Y, 0) * Matrix(TRANS, 60, 20, 60));



	SetCollisionSelf<Frigate>();
	SetCollisionPair<Enemy, Frigate>();
	SetCollisionPair<Enemy, Bullet>();
	SetCollisionTerrain<Bullet>();
}

void FlightScene::SceneEnd()
{

}
