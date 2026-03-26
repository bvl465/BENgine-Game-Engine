#include "Scene.h"
#include "../Game Object/Updatable/UpdatableManager.h"
#include "../Game Object/Drawable/DrawableManager.h"
#include "../Sprite/BENgineSpriteAnimationTimer.h"
#include "../Terrain/TerrainManager.h"
#include "../Game Object/Inputable/KeyboardEventManager.h"
#include "../Camera/CameraManager.h"

Scene::Scene()// : updatableManagerRef(UpdatableManager()), drawableManagerRef(DrawableManager())
{
	//Every scene has its own set of "x-able" managers
	//This way game objects can persist between scenes
	cameraManager = new CameraManager();
	updatableManager = new UpdatableManager();
	drawableManager = new DrawableManager();
	alarmableManager = new AlarmableManager();
	keyboardEventManager = new KeyboardEventManager();
	collisionManager = new CollisionManager();
	animationTimer = new BENgineSpriteAnimationTimer();
	registrationBroker = new SceneRegistrationBroker();
	sprite2DLayerManager = new Sprite2DLayerManager();
	terrainManager = new TerrainManager();

}

Camera* Scene::GetCurrentCamera() const
{
	return cameraManager->GetCurrentCamera();
}

Camera* Scene::GetCurrentCamera2D() const
{
	return cameraManager->GetCurrentCamera2D();
}

TerrainManager* Scene::GetTerrainManager() const
{
	return terrainManager;
}

void Scene::SetCurrentCamera(Camera* cam)
{
	cameraManager->SetCurrentCamera(cam);
}

void Scene::SetCurrentCamera2D(Camera* cam)
{
	cameraManager->SetCurrentCamera2D(cam);
}


Scene::~Scene()
{
	//Delete all the managers that the scene created
	delete cameraManager;
	delete updatableManager;
	delete drawableManager;
	delete alarmableManager;
	delete keyboardEventManager;
	delete collisionManager;
	delete animationTimer;
	delete registrationBroker;
	delete sprite2DLayerManager;
	delete terrainManager;
}

void Scene::DisableLayer(const std::string& layerName)
{
	sprite2DLayerManager->DisableLayer(layerName);
}
void Scene::EnableLayer(const std::string& layerName)
{
	sprite2DLayerManager->EnableLayer(layerName);
}
void Scene::CreateLayers(std::list<std::string> layerNames)
{
	sprite2DLayerManager->CreateLayers(layerNames);
}


void Scene::Register(Updatable* up)
{
	updatableManager->Register(up);
}

void Scene::Deregister(Updatable* up)
{
	updatableManager->Deregister(up);
}

void Scene::Register(Drawable* dr)
{
	drawableManager->Register(dr);
}

void Scene::Deregister(Drawable* dr)
{
	drawableManager->Deregister(dr);
}

void Scene::Register(Alarmable* al, AlarmableManager::ALARM_ID id, float time)
{
	alarmableManager->Register(al, id, time);
}

void Scene::Deregister(Alarmable* al, AlarmableManager::ALARM_ID id)
{
	alarmableManager->Deregister(al, id);
}


void Scene::Register(Inputable* in, AZUL_KEY k, KeyEvent ke)
{
	keyboardEventManager->Register(in, k, ke);
}

void Scene::Deregister(Inputable* in, AZUL_KEY k, KeyEvent ke)
{
	keyboardEventManager->Deregister(in, k, ke);
}

void Scene::SubmitCommand(CommandBase* cmd)
{
	registrationBroker->AddCommand(cmd);
}

CollisionManager* Scene::GetCollisionManager()
{
	return collisionManager;
}

BENgineSpriteAnimationTimer* Scene::GetBENgineSpriteAnimationTimer()
{
	return animationTimer;
}

Sprite2DLayerManager* Scene::GetSprite2DLayerManager() const
{
	return sprite2DLayerManager;
}



void Scene::Update()
{
	//Registration broker is always called first in update.
	registrationBroker->ExecuteCommands();
	
	animationTimer->AddPendingAnimations();
	
	keyboardEventManager->ProcessKeyboardEvents();
	alarmableManager->ProcessAlarms();
	updatableManager->ProcessElements();
	collisionManager->ProcessCollisions();
	animationTimer->ProcessAnimations();

}

void Scene::Draw()
{
	terrainManager->Render();
	drawableManager->ProcessElements();
	//Sprites are ALWAYS drawn last so they will be on top of other drawable objects.
	sprite2DLayerManager->ProcessElements();
}