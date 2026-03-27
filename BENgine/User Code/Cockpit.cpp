#include "Cockpit.h"
#include "../src/BENgine/Sprite/BENgineSpriteCollection.h"
#include "../src/BENgine/Sprite/BENgineSprite.h"
#include "../src/BENgine/Sprite/BENgineAnimatedSprite.h"
#include "../src/BENgine/Scene/SceneManager.h"
#include "../src/BENgine/Sprite/BENgineSpriteAnimation.h"
#include "../src/BENgine/Math Tools/BENgineMathTools.h"
Cockpit::Cockpit() : posX(.5f * (float)(BENgine::GetWidth())), posY(.5f * (float)(BENgine::GetHeight()))
{
	cockpitDamage = new BENgineSpriteAnimation({
		std::make_pair("pCockpitImage", 1.f),
		std::make_pair("pCockpitSlightlyCrackedImage", 1.f)
	});
	cockpitRedAnimation = new BENgineSpriteAnimation({

		std::make_pair("pCockpitSuperCrackedRed1Image", .25f),
		std::make_pair("pCockpitSuperCrackedRed2Image", .5f),
		std::make_pair("pCockpitSuperCrackedRed1Image", .25f),
		std::make_pair("pCockpitSuperCrackedImage", 1.f)
	});
	gameCubeRedAnimation = new BENgineSpriteAnimation({

		std::make_pair("pControllerRed1Image", .25f),
		std::make_pair("pControllerRed2Image", .5f),
		std::make_pair("pControllerRed1Image", .25f),
		std::make_pair("pControllerImage", 1.f)
	});
	
	cockpitSprite = new BENgineAnimatedSprite(cockpitDamage);
	gameCubeSprite = new BENgineAnimatedSprite(gameCubeRedAnimation);
	spriteCollection1 = new BENgineSpriteCollection();

	cockpitSprite->SetLayerPriority(100);
	gameCubeSprite->SetLayerPriority(200);

	//When you have a sprite that stays in place you can set the SpriteAutoUpdateWorldSetting to NEVER so that the graphics object
	//only has its world matrix updated when directly told to do so by calling UpdateWorld on the sprite.
	reticle = new BENgineSprite("pGreenImage", SpriteAutoUpdateWorldSetting::NEVER);
	reticle->SetCenter(0.f, 0.f);
	reticle->SetScaleFactor(.25f, .25f);
	reticle->SetPositionRelative(.5f, .5f);
	reticle->SetLayerPriority(300);
	reticle->AddToLayer("Layer1");
	reticle->UpdateWorld(); //IMPORTANT TO DO SINCE UPDATE WORLD HAS TO BE MANUALLY CALLED





	spriteCollection1->SetDataWithoutTransform(.5f * (float)(BENgine::GetWidth()), .5f * (float)(BENgine::GetHeight()), 0.f, 1.f, 1.f);
	float halfwidth = .5f * (float)(BENgine::GetWidth());
	float halfheight = .5f * (float)(BENgine::GetHeight());
	gameCubeSprite->SetCenter(.75f, -1.f);
	gameCubeSprite->SetPositionAbsolute(halfwidth, halfheight - 450.f);
	gameCubeSprite->SetScaleFactor(.5f, .5f);

	cockpitSprite->SetCenter(0.f, 0.f);
	cockpitSprite->SetPositionAbsolute(.5f * (float)(BENgine::GetWidth()), .5f * (float)(BENgine::GetHeight()));
	spriteCollection1->AddSpriteComponent(cockpitSprite);
	spriteCollection1->AddSpriteComponent(gameCubeSprite);


	SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_UP, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_DOWN, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_D, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_A, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_A, KeyEvent::KEY_RELEASED);
	SubmitKeyRegistration(AZUL_KEY::KEY_D, KeyEvent::KEY_RELEASED);

	SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_LEFT, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_RIGHT, KeyEvent::KEY_PRESSED);

	SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_LEFT, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_RIGHT, KeyEvent::KEY_DOWN);

	SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_UP, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_DOWN, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_A, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_D, KeyEvent::KEY_DOWN);

	SubmitKeyRegistration(AZUL_KEY::KEY_M, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_N, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_1, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_2, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_3, KeyEvent::KEY_PRESSED);


	cockpitSprite->SetAutoUpdateWorldSetting(SpriteAutoUpdateWorldSetting::ON_RENDER);
	cockpitSprite->AddToLayer("CockpitHUD");
	gameCubeSprite->SetAutoUpdateWorldSetting(SpriteAutoUpdateWorldSetting::ON_RENDER);
	gameCubeSprite->AddToLayer("CockpitHUD");
	gameCubeSprite->SetFrame(3); // set the gameCube to the red controller image


}

Cockpit::~Cockpit()
{
	delete spriteCollection1;
	delete gameCubeRedAnimation;
	delete cockpitRedAnimation;
	delete cockpitDamage;
	delete reticle;
	SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_UP, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_DOWN, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_LEFT, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_RIGHT, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_D, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_A, KeyEvent::KEY_PRESSED);

	SubmitKeyDeregistration(AZUL_KEY::KEY_A, KeyEvent::KEY_RELEASED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_D, KeyEvent::KEY_RELEASED);

	SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_UP, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_DOWN, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_A, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_D, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_1, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_2, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_3, KeyEvent::KEY_PRESSED);

	SubmitKeyDeregistration(AZUL_KEY::KEY_M, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_N, KeyEvent::KEY_PRESSED);
}

void Cockpit::KeyPress(AZUL_KEY k)
{
	switch (k) {
	case AZUL_KEY::KEY_M:
		SceneManager::GetCurrentScene()->DisableLayer("CockpitHUD");
		break;
	case AZUL_KEY::KEY_N:
		SceneManager::GetCurrentScene()->EnableLayer("CockpitHUD");
		break;
	case AZUL_KEY::KEY_1:
		cockpitSprite->CancelAnimation();
		cockpitSprite->SetAnimation(cockpitDamage);
		gameCubeSprite->CancelAnimation();

		gameCubeSprite->SetFrame(3);
		cockpitSprite->SetFrame(0);
		break;
	case AZUL_KEY::KEY_2:
		cockpitSprite->CancelAnimation();
		gameCubeSprite->CancelAnimation();
		cockpitSprite->SetAnimation(cockpitDamage);
		gameCubeSprite->SetFrame(3);
		cockpitSprite->SetFrame(1);
		break;
	case AZUL_KEY::KEY_3:
		cockpitSprite->CancelAnimation();
		gameCubeSprite->CancelAnimation();
		cockpitSprite->SetAnimation(cockpitRedAnimation);
		cockpitSprite->LoopAnimationFromFrame(0);
		gameCubeSprite->LoopAnimationFromFrame(0);
		break;
	}
}


void Cockpit::KeyDown(AZUL_KEY k)
{
	switch (k) {
	case AZUL_KEY::KEY_ARROW_UP:

		posY = BENgineMathTools::FloatClamp(posY + 10.f, 240.f, 480.f);
		spriteCollection1->SetPositionAbsolute(posX, posY);
		break;
	case AZUL_KEY::KEY_ARROW_DOWN:
		posY = BENgineMathTools::FloatClamp(posY - 10.f, 240, 480.f);
		spriteCollection1->SetPositionAbsolute(posX, posY);
		break;
	case AZUL_KEY::KEY_A:
		//posX = BENgineMathTools::FloatClamp(posX + 45.f, 160.f, 1120.f);
		gameCubeAngle = BENgineMathTools::FloatClamp(gameCubeAngle + .1f, -MATH_PI3, MATH_PI4);
		gameCubeSprite->SetAngleRadians(gameCubeAngle);
		break;
	case AZUL_KEY::KEY_D:
		//posX = BENgineMathTools::FloatClamp(posX - 45.f, 160.f, 1120.f);
		gameCubeAngle = BENgineMathTools::FloatClamp(gameCubeAngle - .1f, -MATH_PI3, MATH_PI4);
		gameCubeSprite->SetAngleRadians(gameCubeAngle);
		break;
	case AZUL_KEY::KEY_ARROW_RIGHT:
		//posX = BENgineMathTools::FloatClamp(posX - 45.f, 160.f, 1120.f);
		posX = BENgineMathTools::FloatClamp(posX - 40.f, 260.f, 1020.f);
		spriteCollection1->SetPositionAbsolute(posX, posY);
		break;
	case AZUL_KEY::KEY_ARROW_LEFT:
		//posX = BENgineMathTools::FloatClamp(posX - 45.f, 160.f, 1120.f);
		posX = BENgineMathTools::FloatClamp(posX + 40.f, 260.f, 1020.f);
		spriteCollection1->SetPositionAbsolute(posX, posY);
		break;
	}
}

void Cockpit::KeyRelease(AZUL_KEY k)
{
	switch (k) {
	case AZUL_KEY::KEY_D:
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_A) == false) {
			gameCubeSprite->SetAngleRadians(0.f);
			gameCubeAngle = 0.f;
			return;
		}
		break;
	case AZUL_KEY::KEY_A:
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_D) == false) {
			gameCubeSprite->SetAngleRadians(0.f); // resets the angle of the gameCube sprite
			gameCubeAngle = 0.f; //updates what is locally stored
			return;
		}
		break;
	}
}
