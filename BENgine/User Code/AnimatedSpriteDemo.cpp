//Ben La Monica
#include "AnimatedSpriteDemo.h"
#include "../src/BENgine/Asset Managers/Image Manager/ImageManager.h"
#include "../src/BENgine/Sprite/BENgineAnimatedSprite.h"
#include "../src/BENgine/Sprite/BENgineSpriteAnimation.h"
#include "SceneTest.h"
#include "../src/BENgine/Scene/SceneManager.h"
#include "../src/BENgine/Scene/Scene.h"
#include "../src/BENgine/Visualizer/Visualizer.h"

AnimatedSpriteDemo::AnimatedSpriteDemo()
{
	animation1 = new BENgineSpriteAnimation({
		std::make_pair("pMarkedGridMiniImage", 1.f),
		std::make_pair("pGreenImage", 2.5f),
		std::make_pair("pMarkedGridMiniImage", .5f)
		});
	animation2 = new BENgineSpriteAnimation({
		std::make_pair("pMarkedGridMicroImage", 1.f),
		std::make_pair("pGreenImage", 1.f)
		});
	animatedSprite = new BENgineAnimatedSprite(animation1);

	//animation can be changed even after construction
	animatedSprite->SetAnimation(animation2);


	animatedSprite->SetAngleRadians(0.f);

	//animatedSprite->SetScalePixel(100.f, 100.f);
	animatedSprite->SetScaleFactor(1.f, 1.f);

	animatedSprite->SetCenter(0.f, 1.f);
	animatedSprite->SetPositionAbsolute(300.f, 300.f);
	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	animatedSprite->LoopAnimationFromFrame(0);
	animatedSprite->AddToLayer("Layer2");

}

AnimatedSpriteDemo::~AnimatedSpriteDemo()
{

	Updatable::SubmitUpdateDeregistration();

	
	Drawable::SubmitDrawDeregistration();

	delete animatedSprite;
	delete animation1;
	delete animation2;
	
}



void AnimatedSpriteDemo::Update()
{
	
	float angle = animatedSprite->GetAngleRadians();
	animatedSprite->SetAngleRadians(angle + .09f);

}


void AnimatedSpriteDemo::Draw2D()
{
	
	//Don't need to use this method because the animatedSprite is in a layer.
	//If a game object is registered for draw this will be called regardless! (put a break point on this function to see)
	//Keep this in mind when ever using BENgineSprites.
	//You can still call Render on the sprite in here and it will result in it being drawn twice. Uncomment the code below to see the effect.
	
	/*
	const float prevX = animatedSprite->GetPosX();
	const float prevY = animatedSprite->GetPosY();

	//changes the position of the sprite to show that it is being drawn multiple times
	animatedSprite->SetPositionRelative(0.5f, 0.5f);
	animatedSprite->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());

	//sets the sprite back to its original position
	animatedSprite->SetPositionAbsolute(prevX, prevY);
	//*/
}

