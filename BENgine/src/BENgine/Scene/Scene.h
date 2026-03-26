//Ben La Monica
#pragma once
#ifndef _Scene
#define _Scene

#include "SceneRegistrationBroker.h"
#include "../Game Object/Alarmable/AlarmableManager.h"
#include "../Game Object/Inputable/KeyEvent.h"
#include "../Game Object/Collidable/CollisionManager.h"
#include "../Terrain/TerrainManager.h"
#include "AzulCore.h"
#include "../Sprite/Layers/Sprite2DLayerManager.h"
class CameraManager;
class BENgineSpriteAnimationTimer;
class DrawableManager;
class UpdatableManager;
class KeyboardEventManager;
class Updatable;
class Inputable;
class Drawable;
class Alarmable;
class CommandBase;
class TerrainManager;
/**
 Represents a game scene, it contains all GameObject related managers, the CameraManager, TerrainManager, and Sprite2DLayerManager.
 It handles registration and deregistration of game objects.
 It contains an Update and Draw method that are called by the SceneManager. Update is called first, followed by Draw.
 The order of operations is as follows:
 Update:
 1. The registration broker executes all pending registration and deregistration commands.
    This ensures that any changes to the scene's game objects are processed before the rest of the update logic runs.
 2. Animation commands register previous frame are added to the animation timer
 3. Registered keyboard events are processed
 4. Registered Alarmable GameObjects are processed
 5. Registered Updateable GameObjects have update called on them
 6. Registered Collidable GameObjects are processed
 7. Animation commands in the AnimationTimer are processed
 
 Draw:
 1. If the scene has a TerrainObject set then the TerrainObject is rendered
 2. Registered Drawable GameObjects have Draw called on them which is then followed by calling Draw2D on them.
 3. Sprite2DLayers are drawn.

 Scenes are responsible for their own initialization and cleanup.
 */
class Scene
{
	friend class SceneAttorney;

public:

	Scene();
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	//Returns a pointer to the TerrainManager for the current Scene.
	TerrainManager* GetTerrainManager() const;

	//Returns a pointer to the scene's current 3D Camera.
	Camera* GetCurrentCamera() const;


	//Returns a pointer to the scene's current 2D Camera.
	Camera* GetCurrentCamera2D() const;

	//Sets the scene's current 3D camera to the Camera passed in.
	//Parameters:
	//cam - The Camera to set as the Scene's current 3D Camera.
	void SetCurrentCamera(Camera* cam);



	//Sets the scene's current 2D camera to the camera passed in.
	//Parameters:
	//cam - the camera to set as the current 2D camera.
	void SetCurrentCamera2D(Camera* cam);

	//SceneManager is responsible for deleting the scene.
	virtual ~Scene();


	//Called right before ~Scene() is called. Override to provide custom cleanup.
	virtual void SceneEnd() {};



	//Disables the drawing of BENgineSpriteBases stored in the Sprite2DLayer with the name layerName. 
	//Parameters:
	//layerName - The name of the Sprite2DLayer to disable.
	//Note:
	//The Sprite2DLayer must exist in the current scene.
	//Layers DON'T persist between scenes.
	void DisableLayer(const std::string& layerName);



	//Enables the drawing of BENgineSpriteBases stored in the Sprite2DLayer with the name layerName. 
	//Parameters:
	//layerName - The name of the Sprite2DLayer to enable.
	//Note:
	//The Sprite2DLayer must exist in the current scene.
	//Layers DON'T persist between scenes.
	void EnableLayer(const std::string& layerName);

protected:


	//Called by the SceneManager when the Scene is switched to.
	virtual void Initialize() = 0;


	//CreatesSprite2DLayers with the given names. A layer will be drawn over by all the layers that precede it in the list.
	//Parameters:
	//layerNames - A list of the names of the layers in the order 
	virtual void CreateLayers(std::list<std::string> layerNames);


	//Sets up collision detection between two types of collidables.
	//Parameters:
	//C1 - The first collidable type. Must implement Collision(*C2)
	//C2 - The second collidable type. Must implement Collision(*C1)
	template< typename C1, typename C2>
	void SetCollisionPair() {
		collisionManager->SetCollisionPair<C1, C2>();
	}


	//Sets up collision detection with a single type of collidable with itself.
	//Parameters:
	//C - The collidable type to test for collision with others of its type. Must implement Collision(*C)
	template< typename C>
	void SetCollisionSelf() {
		collisionManager->SetCollisionSelf<C>();
	}

	//Sets up collision detection between a type of collidables and the terrain that is within the terrain manager. If a terrain is not set when this is called the engine will crash. This is intentional.
	//Parameters:
	//C - The collidable type to test for collision with the terrain. Will have CollisionTerrain() called on it when it collides with the terrain.
	template< typename C>
	void SetCollisionTerrain() {
		collisionManager->SetCollisionTerrain<C>();
	}
	
private:

	void Register(Updatable* up);
	void Deregister(Updatable* up);

	void Register(Drawable* dr);
	void Deregister(Drawable* dr);

	void Register(Alarmable* al, AlarmableManager::ALARM_ID id, float time);
	void Deregister(Alarmable* al, AlarmableManager::ALARM_ID id);
	

	void Register(Inputable* in, AZUL_KEY k, KeyEvent ke);
	void Deregister(Inputable* in, AZUL_KEY k, KeyEvent ke);
	void SubmitCommand(CommandBase* cmd);

	CollisionManager* GetCollisionManager();
	BENgineSpriteAnimationTimer* GetBENgineSpriteAnimationTimer();
	
	Sprite2DLayerManager* GetSprite2DLayerManager() const;

	//Draw Order:
	//1. If the scene has a TerrainObject set then the TerrainObject is rendered
	//2. Registered Drawable GameObjects have Draw called on them which is then followed by calling Draw2D on them.
	//3. Sprite2DLayers are drawn.
	void Draw();

	//Update Order:
	//1. The registration broker executes all pending registration and deregistration commands.
	//This ensures that any changes to the scene's game objects are processed before the rest of the update logic runs.
	//2. Animation commands register previous frame are added to the animation timer
	//3. Registered keyboard events are processed
	//4. Registered Alarmable GameObjects are processed
	//5. Registered Updateable GameObjects have update called on them
	//6. Registered Collidable GameObjects are processed
	//7. Animation commands in the AnimationTimer are processed
	void Update();
	

	SceneRegistrationBroker* registrationBroker;
	UpdatableManager* updatableManager;
	CollisionManager* collisionManager;
	DrawableManager* drawableManager;
	AlarmableManager* alarmableManager;
	KeyboardEventManager* keyboardEventManager;
	CameraManager* cameraManager;
	BENgineSpriteAnimationTimer* animationTimer;
	Sprite2DLayerManager* sprite2DLayerManager;
	TerrainManager* terrainManager;




};
#endif _Scene