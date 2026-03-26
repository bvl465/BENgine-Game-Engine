#ifndef GAME_H
#define GAME_H

#include "AzulCore.h"

class BENgine: public Engine
{
public:
	//Returns window width
	static int GetWidth();

	//Returns the window height
	static int GetHeight();

	//Set the window width and height
	static void SetWidthHeight(const int width, const int height);

	//Sets the name of the window
	static void SetWindowName(const char* pWindowName);

	//Sets the clear color for the window (background color)
	static void SetClear(float red, float green, float blue, float alpha);


	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!! -= DO. NOT. TOUCH. =-  !!!!!!
	static void BENgineRun();
	//!!!!!! -= DO. NOT. TOUCH. =-  !!!!!!
	static void BENgineDestroy();
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	

private:
	static BENgine* ptrInstance; //Part of singleton set up
	BENgine() = default;
	static BENgine& Instance();
	friend class BENgineAttorney;
	
	//Returns the time in seconds
	static float GetTime();

	//-Methods engine programmer need to overload-

	virtual void Initialize();
	virtual void LoadContent(); 
	virtual void Update();
	virtual void Draw();
	virtual void UnLoadContent();

	//--------------------------------------------

	//Users put the resources they want to load in LoadResources.cpp (Textures, ShaderObjects, TerrainObjects, Textures, Images, and SpriteFonts).
	//Textures must be loaded before images and terrain. They can specify the start scene after everything has been loaded.
	//After the user has loaded everything they want they also need to SceneManager::SetNextScene(Scene* scene) to set the first active scene.
	void LoadAllResources();

	//Initializes the engine window
	void GameInitialize();

	//Users put the code they want to run at the end of the game here.
	//The user still has access to the following managers when GameEnd() is called
	//ModelManager
	//ShaderManager
	//TextureManager
	//ImageManager
	//Visualizer
	//TerrainObjectManager
	//SceneManager
	//SpriteFontManager
	//TimeManager
	void GameEnd();

	
};

#endif