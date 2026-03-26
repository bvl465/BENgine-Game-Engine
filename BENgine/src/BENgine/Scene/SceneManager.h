//Ben La Monica
#pragma once
#ifndef _SceneManager
#define _SceneManager
class SceneManagerStrategyBase;
class Scene;
class SceneChangeStrategy;
class SceneNullStrategy;


//Manages the current scene, scene transitions, and scene lifecycle in the engine.
class SceneManager
{
public:

	//Schedules a scene change to take place at the end of the current frame to the specified scene passed in.
	//Parameters:
	//scene - Pointer to the Scene to set as the next active scene.
	static void SetNextScene(Scene* scene);

	//Returns a pointer to the current active scene.
	static Scene* GetCurrentScene();


private:
	friend class SceneManagerAttorney;

	SceneManager();
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	~SceneManager() = default;

	static SceneManager& Instance(); // Access reference (all public methods will be static)

	//Checks if a scene change is scheduled and if so changes the current scene to the next scene then calls Update() on the current scene.
	static void Update();

	//Calls Draw() on the current scene.
	static void Draw();

	//Calls SceneEnd() on the current scene then deletes the current scene.
	static void Delete();

	//Deletes the current scene and sets the current scene to the scene passed and calls Initialize() on the new current scene.
	//Parameters:
	//scene - Pointer to the Scene to change to.
	static void ChangeScene(Scene* scene);

	void privChangeScene(Scene* scene);

	
	void privSetNextScene(Scene* scene);

	Scene* privGetCurrentScene();

	void privUpdate();
	void privDraw();


	static SceneManager* ptrInstance;
	Scene* curScene = nullptr;
	
	SceneManagerStrategyBase* curSceneStrategy = nullptr;
	SceneChangeStrategy* sceneChangeStrategy = nullptr;
	SceneNullStrategy* sceneNullStrategy = nullptr;



};
#endif _SceneManager