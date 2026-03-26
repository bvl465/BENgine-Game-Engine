//Ben La Monica

#include "../BENgine/BENgine.h"
#include "../BENgine/Asset Managers/Shader Manager/ShaderManager.h"
#include "../BENgine/Asset Managers/Texture Manager/TextureManager.h"
#include "../BENgine/Asset Managers/Model Manager/ModelManager.h"
#include "../BENgine/Asset Managers/Image Manager/ImageManager.h"
#include "../BENgine/Scene/SceneManager.h"
#include "../BENgine/Asset Managers/Terrain Object Manager/TerrainObjectManager.h"
#include "../User Code/SceneDemo.h"
#include "../BENgine/Sprite/SpriteFontManager.h"

//Users put the resources they want to load here. Textures must be loaded before images and terrain.
void BENgine::LoadAllResources() {


	//Models use Edward Keenan's .azul file type. Use the converter to turn .FBX files in .azul files.
	
	//Models
	ModelManager::Load("pModelAxis", "Axis.azul");
	ModelManager::Load("pModelSpaceFrigate", "space_frigate.azul");
	ModelManager::Load("PModelSphere", Model::PreMadeModels::UnitSphere);
	ModelManager::Load("PModelBox", Model::PreMadeModels::UnitBox_WF);
	ModelManager::Load("pModelCottage", "Cottage.azul");
	ModelManager::Load("pModelXWing", "Xwing.azul");
	ModelManager::Load("pPixelTankBody", "Pixel_Tank_Body.azul");
	ModelManager::Load("pPixelTankTurret", "Pixel_Tank_Turret.azul");
	ModelManager::Load("pPixelTankBarrel", "Pixel_Tank_Barrel.azul");
	ModelManager::Load("pModelPlane", 400, 2, 2);
	

	//Textures
	TextureManager::Load("pSpaceFrigateTex", "space_frigate.tga");
	TextureManager::Load("pTextPlane", "grid.tga");
	TextureManager::Load("pStitchTexture", "stitch.tga");
	TextureManager::Load("pMarkedGridTexture", "MarkedGrid.tga");
	TextureManager::Load("pMarkedGridSmallTexture", "MarkedGridSmall.tga");
	TextureManager::Load("pMarkedGridMiniTexture", "MarkedGridMini.tga");
	TextureManager::Load("pXYMiniTexture", "XYMini.tga");
	TextureManager::Load("pMarkedGridMicroTexture", "MarkedGridMicro.tga");
	TextureManager::Load("pGreenTexture", "Green.tga");
	TextureManager::Load("pCottageTexture", "Cabintexture.tga");
	TextureManager::Load("pHeightMapTest16", "HMTest16.tga");
	TextureManager::Load("pHeightMapTest", "HMTest.tga");
	TextureManager::Load("pHeightMapTestOdd", "HMTestOdd.tga");
	TextureManager::Load("pXWingTexture", "XwingUVs.tga");
	TextureManager::Load("pCockpitTexture", "Cockpit.tga");
	TextureManager::Load("pCockpitSlightlyCrackedTexture", "CockpitSlightlyCracked.tga");
	TextureManager::Load("pCockpitSuperCrackedTexture", "CockpitSuperCracked.tga");
	TextureManager::Load("pCockpitSuperCrackedRed1Texture", "CockpitSuperCrackedRed1.tga");
	TextureManager::Load("pCockpitSuperCrackedRed2Texture", "CockpitSuperCrackedRed2.tga");
	TextureManager::Load("pControllerTexture", "GameCubeController.tga");
	TextureManager::Load("pControllerRed1Texture", "GameCubeControllerRed1.tga");
	TextureManager::Load("pControllerRed2Texture", "GameCubeControllerRed2.tga");
	//TextureManager::Load("pCourier_NewBlackTexture", "Courier_New.tga");
	
	//Shaders
	ShaderManager::Load("pShaderObject_texture", "textureFlatRender");
	ShaderManager::Load("pShaderObject_textureLight", "textureLightRender");
	ShaderManager::Load("pShaderObject_constantColor", "colorConstantRender");
	ShaderManager::Load("pShaderObject_colorNoTexture", "colorNoTextureRender");

	//Images
	ImageManager::Load("pStitchImage", TextureManager::GetTexture("pStitchTexture"));
	ImageManager::Load("pGreenImage", TextureManager::GetTexture("pGreenTexture"));
	ImageManager::Load("pMarkedGridImage", TextureManager::GetTexture("pMarkedGridTexture"));
	ImageManager::Load("pMarkedGridMicroImage", TextureManager::GetTexture("pMarkedGridMicroTexture"));
	ImageManager::Load("pMarkedGridMiniImage", TextureManager::GetTexture("pMarkedGridMiniTexture"));
	ImageManager::Load("pXYMiniImage", TextureManager::GetTexture("pXYMiniTexture"));
	ImageManager::Load("pMarkedGridSmallImage", TextureManager::GetTexture("pMarkedGridSmallTexture"));
	ImageManager::Load("pCockpitImage", TextureManager::GetTexture("pCockpitTexture"));
	ImageManager::Load("pCockpitSlightlyCrackedImage", TextureManager::GetTexture("pCockpitSlightlyCrackedTexture"));
	ImageManager::Load("pCockpitSuperCrackedImage", TextureManager::GetTexture("pCockpitSuperCrackedTexture"));
	ImageManager::Load("pCockpitSuperCrackedRed1Image", TextureManager::GetTexture("pCockpitSuperCrackedRed1Texture"));
	ImageManager::Load("pCockpitSuperCrackedRed2Image", TextureManager::GetTexture("pCockpitSuperCrackedRed2Texture"));
	ImageManager::Load("pControllerImage", TextureManager::GetTexture("pControllerTexture"));
	ImageManager::Load("pControllerRed1Image", TextureManager::GetTexture("pControllerRed1Texture"));
	ImageManager::Load("pControllerRed2Image", TextureManager::GetTexture("pControllerRed2Texture"));

	//Terrain
	TerrainObjectManager::Load("pTerrainTestTerrainObject", "HMTest.tga", 550, 25, 12, TextureManager::GetTexture("pHeightMapTest"), 2, 3);
	TerrainObjectManager::Load("pTerrainTest2TerrainObject", "HMTestOdd.tga", 1000, 50, -12, TextureManager::GetTexture("pHeightMapTestOdd"), 7, 18);

	//SpriteFonts
	SpriteFontManager::Load("pCourierNew", "Courier_New.xml", "pCourier_NewBlackTexture", "Courier_New.tga");

	SceneManager::SetNextScene(new SceneDemo());


}