//Ben La Monica
#include "SceneManager.h"
#include "SceneAttorney.h"
#include "Scene.h"
#include "SceneNull.h"
#include "SceneNullStrategy.h"
#include "SceneChangeStrategy.h"
SceneManager* SceneManager::ptrInstance = nullptr;

void SceneManager::Delete()
{
	if (ptrInstance != nullptr) {
		ptrInstance->curScene->SceneEnd();
		delete ptrInstance->curScene;
		delete ptrInstance->sceneChangeStrategy;
		delete ptrInstance->sceneNullStrategy;
		delete ptrInstance;
		ptrInstance = nullptr;
	}
}

void SceneManager::ChangeScene(Scene* scene)
{
	Instance().privChangeScene(scene);
}

void SceneManager::privChangeScene(Scene* scene)
{
	curScene->SceneEnd();
	delete curScene;
	curScene = scene;
	SceneAttorney::GameLoop::Initialize(curScene);
	curSceneStrategy = sceneNullStrategy;
	
}

void SceneManager::privSetNextScene(Scene* scene)
{
	curSceneStrategy = sceneChangeStrategy;
	sceneChangeStrategy->SetNextScene(scene);
}



SceneManager& SceneManager::Instance()
{
	//part of singleton set up
	if (ptrInstance == nullptr) {
		ptrInstance = new SceneManager();
	}
	return *ptrInstance;
}

SceneManager::SceneManager()
{
	curScene = new SceneNull();
	sceneNullStrategy = new SceneNullStrategy();
	sceneChangeStrategy = new SceneChangeStrategy();
	curSceneStrategy = sceneNullStrategy;
	//curScene = new SceneNull();
}

void SceneManager::SetNextScene(Scene* scene)
{
	Instance().privSetNextScene(scene);
}

Scene* SceneManager::GetCurrentScene()
{
	return Instance().privGetCurrentScene();
}

void SceneManager::Update()
{
	Instance().privUpdate();
}
void SceneManager::Draw()
{
	Instance().privDraw();
}

Scene* SceneManager::privGetCurrentScene()
{
	return curScene;
}


void SceneManager::privUpdate()
{
	curSceneStrategy->Execute();
	SceneAttorney::GameLoop::Update(curScene);
}

void SceneManager::privDraw()
{
	SceneAttorney::GameLoop::Draw(curScene);
}
