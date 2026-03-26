//Ben La Monica
#pragma once
#ifndef _SceneAttorney
#define _SceneAttorney
#include "AzulCore.h"

#include "Scene.h"
class SceneAttorney
{
public:
	class GameLoop
	{
	private:
		friend class SceneManager;
		static void Update(Scene* scene) { scene->Update(); }
		static void Draw(Scene* scene) { scene->Draw(); }
		static void Initialize(Scene* scene) { scene->Initialize(); }
	};

public:
	class Update
	{
		friend class Updatable;

	private:
		static void Register(Scene* scene, Updatable* up) { scene->Register(up); }

		//Removes the passed Updatable from the UpdatableManager's storageList to stop being updated each frame. Called by the Updatable's SubmitUpdateDeregistration() function.
		//Parameters:
		//scene - the Scene to deregister from
		//up - the Updatable to deregister
		static void Deregister(Scene* scene, Updatable* up) { scene->Deregister(up); }

		//Submits an UpdatabaleRegistrationCommand to the SceneRegistrationBroker to have it added to the UpdatableManager's storageList to be updated each frame.
		//Parameters:
		//scene - the Scene to submit the command to
		//cmd - the Command to submit to the SceneRegistrationBroker
		static void SubmitCommand(Scene* scene, CommandBase* cmd) { scene->SubmitCommand(cmd); }
	};

public:
	class Draw
	{
		friend class Drawable;

	private:
		//Adds the passed Drawable to the DrawableManager's storageList to be drawn each frame. Called by the Drawable's SceneRegistration() function.
		//Parameters:
		//scene - the Scene to register to
		//dr - the Drawable to register
		static void Register(Scene* scene, Drawable* dr) { scene->Register(dr); }

		//Removes the passed Drawable from the DrawableManager's storageList to stop being drawn each frame. Called by the Drawable's SceneDeegistration() function.
		//Parameters:
		//scene - the Scene to deregister from
		//dr - the Drawable to deregister
		static void Deregister(Scene* scene, Drawable* dr) { scene->Deregister(dr); }
		static void SubmitCommand(Scene* scene, CommandBase* cmd) { scene->SubmitCommand(cmd); }
	};

public:
	class Alarm
	{
		friend class Alarmable;
	private:
		static void Register(Scene* scene, Alarmable* al, AlarmableManager::ALARM_ID id, float time) { scene->Register(al, id, time); }
		static void Deregister(Scene* scene, Alarmable* al, AlarmableManager::ALARM_ID id) { scene->Deregister(al, id); }
		static void SubmitCommand(Scene* scene, CommandBase* cmd) { scene->SubmitCommand(cmd); }
	};
public:
	class Input
	{
		friend class Inputable;
	private:
		static void Register(Scene* scene, Inputable* in, AZUL_KEY k, KeyEvent ke) { scene->Register(in, k, ke); }
		static void Deregister(Scene* scene, Inputable* in, AZUL_KEY k, KeyEvent ke) { scene->Deregister(in, k, ke); }
		static void SubmitCommand(Scene* scene, CommandBase* cmd) { scene->SubmitCommand(cmd); }
	};
public:
	class Collision
	{
		friend class Collidable;
	private:
		static void SubmitCommand(Scene* scene, CommandBase* cmd) { scene->SubmitCommand(cmd); }
		static CollisionManager* GetCollisionManager(Scene* scene) { return scene->GetCollisionManager(); }
	};
public:
	class GameObj
	{
		friend class GameObject;
	private:
		static void SubmitCommand(Scene* scene, CommandBase* cmd) { scene->SubmitCommand(cmd); }
	};
public:
	class AnimatedSprite
	{
		friend class BENgineSpriteAnimationCommandBase;
	
	private:
		static BENgineSpriteAnimationTimer* GetAnimationTimer(Scene* scene) { return scene->GetBENgineSpriteAnimationTimer(); }
	};

public:
	class Layer
	{
		friend class BENgineSpriteBase;
	private:
		static Sprite2DLayerManager* GetSprite2DLayerManager(Scene* scene) { return scene->GetSprite2DLayerManager(); }
	};
};
#endif _SceneAttorney