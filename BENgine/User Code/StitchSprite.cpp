//Ben La Monica
#include "StitchSprite.h"
#include "../src/BENgine/Asset Managers/Image Manager/ImageManager.h"
#include "../src/BENgine/Sprite/BENgineSprite.h"
#include "SceneTest.h"
#include "../src/BENgine/Scene/SceneManager.h"
#include "../src/BENgine/Scene/Scene.h"
#include "../src/BENgine/Visualizer/Visualizer.h"

StitchSprite::StitchSprite()
{
	stitch = new BENgineSprite(std::string("pStitchImage"));
	stitch->SetAngleRadians(0.f);
	stitch->SetScaleFactor(1.f, 1.f);
	stitch->SetScaleFactor(.25f, .25f);
	stitch->SetCenter(0.f, 0.f);
	stitch->SetPositionAbsolute(300.f, 300.f);
	//The graphics objects sprite will only update on render
	stitch->SetAutoUpdateWorldSetting(SpriteAutoUpdateWorldSetting::ON_RENDER);
	Updatable::SubmitUpdateRegistration();
	
	stitch->SetLayerPriority(300);
	stitch->AddToLayer("Layer2");
}

StitchSprite::~StitchSprite()
{

	Updatable::SubmitUpdateDeregistration();

	delete stitch;
}


void StitchSprite::Update()
{

	stitch->RotateAboutAbsolutePointRadians(350.f, 350.f, .05f);
	stitch->SetAngleRadians(0);

}


