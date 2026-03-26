#include "SceneDemo.h"
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


SceneDemo::~SceneDemo()
{
	delete stitch;
	//delete stitch2;
	delete plane;
	delete frigate;
	//delete frigate2;
	delete axis;
	delete freeCam;
	delete enemy;
	delete enemy2;
	//delete cockpit;
	//delete terrain;
	//delete animatedsprite;
	delete spriteCollectionDemo;
}

void SceneDemo::Initialize()
{
	(SceneManager::GetCurrentScene())->GetTerrainManager()->SetCurrentTerrain("pTerrainTestTerrainObject");
	//terrain = new Terrain("HMTest16.tga", 400, 100, 0, TextureManager::GetTexture("pHeightMapTest"), 1, 1);
	CreateLayers({ "Layer1", "Layer2", "Layer3" });
	freeCam = new FreeCamera();
	SetCurrentCamera(freeCam->GetCamera());
	//starFighter = new StarFighter();
	

	frigate = new Frigate();
	//cockpit = new Cockpit();
	//frigate2 = new Frigate();
	//frigate2->IgnoreKeyPress();
	plane = new WorldPlane();
	axis = new Axis();
	stitch = new StitchSprite();
	
	//stitch2 = new StitchSprite();
	//stitch2->SetUpdateMethod(false);
	enemy = new Enemy();
	enemy2 = new Enemy();
	enemy2->SetWorld(Matrix(SCALE, 1.f, 1.f, 1.f) * Matrix(ROT_Y, 0) * Matrix(TRANS, 60, 20, 60));

	//animatedsprite = new AnimatedSpriteDemo();
	spriteCollectionDemo = new SpriteCollectionDemo();


	SetCollisionSelf<Frigate>();
	SetCollisionPair<Enemy, Frigate>();
	SetCollisionPair<Enemy, Bullet>();
	SetCollisionTerrain<Bullet>();
}

void SceneDemo::SceneEnd()
{


}
