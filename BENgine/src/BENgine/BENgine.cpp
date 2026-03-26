#include "AzulCore.h"
#include "BENgine.h"
#include "./Asset Managers/Model Manager/ModelManager.h"
#include "./Asset Managers/Shader Manager/ShaderManager.h"
#include "./Asset Managers/Texture Manager/TextureManager.h"
#include "./Scene/SceneManager.h"
#include "./Scene/Scene.h"
#include "./Camera/CameraManager.h"
#include "./Asset Managers/Model Manager/ModelManagerAttorney.h"
#include "./Asset Managers/Shader Manager/ShaderManagerAttorney.h"
#include "./Asset Managers/Texture Manager/TextureManagerAttorney.h"
#include "./Asset Managers/Image Manager/ImageManagerAttorney.h"
#include "./Time/TimeManagerAttorney.h"
#include "./Scene/SceneManagerAttorney.h"
#include "./Visualizer/VisualizerAttorney.h"
#include "./Sprite/SpriteFontManagerAttorney.h"
#include "Asset Managers/Terrain Object Manager/TerrainObjectManagerAttorney.h"


//NO USER CODE GOES HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

BENgine* BENgine::ptrInstance = nullptr;


BENgine& BENgine::Instance()
{
	if (ptrInstance == nullptr) {
		ptrInstance = new BENgine();
	}
	return *ptrInstance;
}

//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void BENgine::Initialize()
{
	this->GameInitialize();

}

//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void BENgine::LoadContent()
{
	this->LoadAllResources(); //LoadAllResources is user defined

	//SceneManager::InitStartScene();

}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void BENgine::Update()
{
	TimeManagerAttorney::Time::ProcessTime();
	SceneManagerAttorney::GameLoop::Update();
}

//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void BENgine::Draw()
{
	SceneManagerAttorney::GameLoop::Draw();
	VisualizerAttorney::GameLoop::VisualizeAll();

}



//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void BENgine::UnLoadContent()
{
	this->GameEnd(); //User code


	//Asset manager clean up
	//--------------------------------------------------
	// Telling the attorneys to call the private delete 
	// method on their respective asset managers
	ShaderManagerAttorney::Delete();
	ModelManagerAttorney::Delete();
	TextureManagerAttorney::Delete();
	ImageManagerAttorney::Delete();
	VisualizerAttorney::GameLoop::Delete();
	TerrainObjectManagerAttorney::Delete();
	//--------------------------------------------------


	//Scene clean up
	//--------------------------------------------------
	//ALSO calls virtual destructor for scene base class
	SceneManagerAttorney::GameLoop::Delete();
	//--------------------------------------------------

	SpriteFontManagerAttorney::Delete();

	TimeManagerAttorney::Time::Delete();

}

float BENgine::GetTime()
{
	return Instance().GetTimeInSeconds();
}

int BENgine::GetWidth()
{
	return Instance().getWidth();
}

int BENgine::GetHeight()
{
	return Instance().getHeight();
}

void BENgine::SetWidthHeight(const int width, const int height)
{
	Instance().setWidthHeight(width, height);
}

void BENgine::SetWindowName(const char* pWindowName)
{
	Instance().setWindowName(pWindowName);
}

void BENgine::SetClear(float red, float green, float blue, float alpha)
{
	Instance().SetClearColor(red, green, blue, alpha);
}

void BENgine::BENgineRun()
{
	Instance().run();
}

void BENgine::BENgineDestroy()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}


