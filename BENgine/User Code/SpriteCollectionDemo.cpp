#include "SpriteCollectionDemo.h"
#include "../src/BENgine/Sprite/BENgineSpriteCollection.h"
#include "../src/BENgine/Sprite/BENgineSprite.h"
#include "../src/BENgine/Sprite/BENgineAnimatedSprite.h"
#include "../src/BENgine/Scene/SceneManager.h"
#include "../src/BENgine/Sprite/BENgineSpriteAnimation.h"
SpriteCollectionDemo::SpriteCollectionDemo()
{
	animation1 = new BENgineSpriteAnimation({
		std::make_pair("pGreenImage", 1.f),
		std::make_pair("pMarkedGridMiniImage", 1.f)
	});

	animation11 = new BENgineSpriteAnimation({
		std::make_pair("pGreenImage", 1.f),
		std::make_pair("pMarkedGridMiniImage", 1.f)
		});

	animation2 = new BENgineSpriteAnimation({
		std::make_pair("pGreenImage", .25f),
		//std::make_pair("pStitchImage", .25f),
		std::make_pair("pMarkedGridMiniImage", .25f)
	});

	animation22 = new BENgineSpriteAnimation({
		std::make_pair("pGreenImage", .25f),
		std::make_pair("pMarkedGridMiniImage", .25f)
	});
	animatedSprite1 = new BENgineAnimatedSprite(animation1, SpriteAutoUpdateWorldSetting::ON_RENDER);
	animatedSprite2 = new BENgineAnimatedSprite(animation1, SpriteAutoUpdateWorldSetting::ON_RENDER);

	//animatedSprite1->SetFrameCenteringSetting(BENgineAnimatedSprite::FrameCenteringSetting::USE_ANIMATION_CENTER);

	regularSprite1 = new BENgineSprite(std::string("pMarkedGridMiniImage"), SpriteAutoUpdateWorldSetting::ON_TRANSFORM);
	regularSprite2 = new BENgineSprite(std::string("pMarkedGridMiniImage"), SpriteAutoUpdateWorldSetting::ON_TRANSFORM);
	spriteCollection1 = new BENgineSpriteCollection();
	spriteCollection2 = new BENgineSpriteCollection();
	spriteCollection3 = new BENgineSpriteCollection();

	testSprite = new BENgineSprite(std::string("pMarkedGridMiniImage"), SpriteAutoUpdateWorldSetting::ON_TRANSFORM);
	testSprite->SetCenter(-1.f, -1.f);
	testSprite->SetPositionAbsolute(100.f, 500.f);

	//Sprites can have their own priority within a layer
	regularSprite1->SetLayerPriority(100);
	regularSprite2->SetLayerPriority(0);
	animatedSprite1->SetLayerPriority(300);
	animatedSprite2->SetLayerPriority(400);

	//sets the position angle and scale of the collection without applying it to the sprites with in the collection
	spriteCollection1->SetDataWithoutTransform(300.f, 300.f, 0.f, 1.f, 1.f);
	spriteCollection2->SetDataWithoutTransform(364.f, 300.f, 0.f, 1.f, 1.f);
	spriteCollection3->SetDataWithoutTransform(428.f, 300.f, 0.f, 1.f, 1.f);

	//Graphic used to show the orientation of the collection.
	collectionViewer = new BENgineSprite(std::string("pXYMiniImage"), SpriteAutoUpdateWorldSetting::ON_RENDER);
	collectionViewer->SetLayerPriority(500);
	collectionViewer->SetPositionAbsolute(spriteCollection1->GetPosX(), spriteCollection1->GetPosY());
	collectionViewer->SetAngleRadians(spriteCollection1->GetAngleRadians());
	collectionViewer->SetScaleFactor(spriteCollection1->GetScaleX(), spriteCollection1->GetScaleY());
	

	regularSprite1->SetCenter(-1.f, 0.f);
	regularSprite1->SetPositionAbsolute(300.f, 300.f);
	spriteCollection1->AddSpriteComponent(regularSprite1);
	spriteCollection1->AddSpriteComponent(spriteCollection2);
	
	regularSprite2->SetCenter(-1.f, 0.f);
	regularSprite2->SetPositionAbsolute(364.f, 300.f);

	spriteCollection2->AddSpriteComponent(regularSprite2);
	spriteCollection2->AddSpriteComponent(spriteCollection3);

	animatedSprite1->SetCenter(-1.f, -1.f);
	animatedSprite2->SetCenter(-1.f, 1.f);

	animatedSprite1->SetPositionAbsolute(428.f, 300.f);
	animatedSprite2->SetPositionAbsolute(428.f, 300.f);

	spriteCollection3->AddSpriteComponent(animatedSprite1);

	//animatedSprite1->SetAngleRadians(MATH_PI / 4.f);

	//animatedSprite2->SetFrame(1);

	spriteCollection3->AddSpriteComponent(animatedSprite2);


	SubmitKeyRegistration(AZUL_KEY::KEY_1, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_2, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_3, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_4, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_5, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_6, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_7, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_8, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_LEFT_BRACKET, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_RIGHT_BRACKET, KeyEvent::KEY_PRESSED);

	SubmitKeyRegistration(AZUL_KEY::KEY_1, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_2, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_3, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_4, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_5, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_6, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_7, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_8, KeyEvent::KEY_DOWN);


	SubmitKeyRegistration(AZUL_KEY::KEY_J, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_K, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_I, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_L, KeyEvent::KEY_PRESSED);



	SubmitKeyRegistration(AZUL_KEY::KEY_J, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_K, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_I, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_L, KeyEvent::KEY_DOWN);

	SubmitKeyRegistration(AZUL_KEY::KEY_Z, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_X, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_C, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_M, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_N, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_EQUAL, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_MINUS, KeyEvent::KEY_PRESSED);


	regularSprite1->AddToLayer("Layer1");
	regularSprite2->AddToLayer("Layer1");
	animatedSprite1->AddToLayer("Layer1");

	//testSprite->AddToLayer("Layer2");

	collectionViewer->AddToLayer("Layer1");
	animatedSprite2->AddToLayer("Layer1");

}


SpriteCollectionDemo::~SpriteCollectionDemo()
{
	delete spriteCollection1;
	delete animation1;
	delete animation2;
	delete animation11;
	delete animation22;
	delete testSprite;
	delete collectionViewer;

	SubmitKeyDeregistration(AZUL_KEY::KEY_1, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_2, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_3, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_4, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_5, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_6, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_7, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_8, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_LEFT_BRACKET, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_RIGHT_BRACKET, KeyEvent::KEY_PRESSED);

	SubmitKeyDeregistration(AZUL_KEY::KEY_1, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_2, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_3, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_4, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_5, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_6, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_7, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_8, KeyEvent::KEY_DOWN);

	SubmitKeyDeregistration(AZUL_KEY::KEY_J, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_K, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_I, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_L, KeyEvent::KEY_PRESSED);

	SubmitKeyDeregistration(AZUL_KEY::KEY_J, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_K, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_I, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_L, KeyEvent::KEY_DOWN);

	SubmitKeyDeregistration(AZUL_KEY::KEY_Z, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_X, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_C, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_M, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_N, KeyEvent::KEY_PRESSED);

	SubmitKeyDeregistration(AZUL_KEY::KEY_EQUAL, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_MINUS, KeyEvent::KEY_PRESSED);
}


void SpriteCollectionDemo::KeyPress(AZUL_KEY k)
{

	switch (k) {
	case AZUL_KEY::KEY_1:

		spriteCollection1->RotateByRadians(.05f);

		collectionViewer->SetPositionAbsolute(spriteCollection1->GetPosX(), spriteCollection1->GetPosY());
		collectionViewer->SetAngleRadians(spriteCollection1->GetAngleRadians());
		collectionViewer->SetScaleFactor(spriteCollection1->GetScaleX(), spriteCollection1->GetScaleY());
		collectionViewer->SetFlipX(spriteCollection1->GetFlipX());
		collectionViewer->SetFlipY(spriteCollection1->GetFlipY());
		break;
	case AZUL_KEY::KEY_2:
		spriteCollection1->RotateByRadians(-.05f);

		collectionViewer->SetPositionAbsolute(spriteCollection1->GetPosX(), spriteCollection1->GetPosY());
		collectionViewer->SetAngleRadians(spriteCollection1->GetAngleRadians());
		collectionViewer->SetScaleFactor(spriteCollection1->GetScaleX(), spriteCollection1->GetScaleY());
		collectionViewer->SetFlipX(spriteCollection1->GetFlipX());
		collectionViewer->SetFlipY(spriteCollection1->GetFlipY());
		break;
	case AZUL_KEY::KEY_3:
		spriteCollection2->RotateByRadians(.05f);
		break;
	case AZUL_KEY::KEY_4:
		spriteCollection2->RotateByRadians(-.05f);
		break;
	case AZUL_KEY::KEY_5:
		spriteCollection3->RotateByRadians(.05f);
		break;
	case AZUL_KEY::KEY_6:
		spriteCollection3->RotateByRadians(-.05f);
		break;
	case AZUL_KEY::KEY_7:
		animatedSprite1->RotateByRadians(.05f);
		animatedSprite2->RotateByRadians(-.05f);
		break;
	case AZUL_KEY::KEY_8:
		animatedSprite1->RotateByRadians(-.05f);
		animatedSprite2->RotateByRadians(.05f);
		break;
	case AZUL_KEY::KEY_J:
		
		if (spriteCollection1->GetFlipY() == 1.f) {
			spriteCollection1->ReflectOverLocalYAxis();
			//testSprite->ReflectOverLocalYAxis();
			
		}
		spriteCollection1->TransformPositionAbsolute(-2.f, 0.f);

		collectionViewer->SetPositionAbsolute(spriteCollection1->GetPosX(), spriteCollection1->GetPosY());
		collectionViewer->SetAngleRadians(spriteCollection1->GetAngleRadians());
		collectionViewer->SetScaleFactor(spriteCollection1->GetScaleX(), spriteCollection1->GetScaleY());
		collectionViewer->SetFlipX(spriteCollection1->GetFlipX());
		collectionViewer->SetFlipY(spriteCollection1->GetFlipY());
		break;
	case AZUL_KEY::KEY_K:
		if (spriteCollection1->GetFlipX() == 1.f) {
			spriteCollection1->ReflectOverLocalXAxis();
			//testSprite->ReflectOverLocalXAxis();
		}
		spriteCollection1->TransformPositionAbsolute(0.f, -2.f);

		collectionViewer->SetPositionAbsolute(spriteCollection1->GetPosX(), spriteCollection1->GetPosY());
		collectionViewer->SetAngleRadians(spriteCollection1->GetAngleRadians());
		collectionViewer->SetScaleFactor(spriteCollection1->GetScaleX(), spriteCollection1->GetScaleY());
		collectionViewer->SetFlipX(spriteCollection1->GetFlipX());
		collectionViewer->SetFlipY(spriteCollection1->GetFlipY());
		break;
	case AZUL_KEY::KEY_L:
		if (spriteCollection1->GetFlipY() == -1.f) {
			spriteCollection1->ReflectOverLocalYAxis();
			//testSprite->ReflectOverLocalYAxis();
		}
		spriteCollection1->TransformPositionAbsolute(2.f, 0.f);

		collectionViewer->SetPositionAbsolute(spriteCollection1->GetPosX(), spriteCollection1->GetPosY());
		collectionViewer->SetAngleRadians(spriteCollection1->GetAngleRadians());
		collectionViewer->SetScaleFactor(spriteCollection1->GetScaleX(), spriteCollection1->GetScaleY());
		collectionViewer->SetFlipX(spriteCollection1->GetFlipX());
		collectionViewer->SetFlipY(spriteCollection1->GetFlipY());
		break;
	case AZUL_KEY::KEY_I:
		if (spriteCollection1->GetFlipX() == -1.f) {
			spriteCollection1->ReflectOverLocalXAxis();
			//testSprite->ReflectOverLocalXAxis();
		}
		spriteCollection1->TransformPositionAbsolute(0.f, 2.f);

		collectionViewer->SetPositionAbsolute(spriteCollection1->GetPosX(), spriteCollection1->GetPosY());
		collectionViewer->SetAngleRadians(spriteCollection1->GetAngleRadians());
		collectionViewer->SetScaleFactor(spriteCollection1->GetScaleX(), spriteCollection1->GetScaleY());
		collectionViewer->SetFlipX(spriteCollection1->GetFlipX());
		collectionViewer->SetFlipY(spriteCollection1->GetFlipY());
		break;
	case AZUL_KEY::KEY_Z:
		animatedSprite1->SetAnimation(animation1);
		animatedSprite2->SetAnimation(animation1);
		animatedSprite1->LoopAnimationFromFrame(0);
		animatedSprite2->LoopAnimationFromFrame(0);
		break;
	case AZUL_KEY::KEY_X:
		animatedSprite1->SetAnimation(animation2);
		animatedSprite2->SetAnimation(animation2);
		animatedSprite1->LoopAnimationFromFrame(0);
		animatedSprite2->LoopAnimationFromFrame(0);
		break;
	case AZUL_KEY::KEY_C:
		animatedSprite1->CancelAnimation();
		animatedSprite2->CancelAnimation();
		break;
	case AZUL_KEY::KEY_M:
		SceneManager::GetCurrentScene()->DisableLayer("Layer1");
		break;
	case AZUL_KEY::KEY_N:
		SceneManager::GetCurrentScene()->EnableLayer("Layer1");
		break;
	case AZUL_KEY::KEY_MINUS:
		scaleX -= .5f;
		//testSprite->SetScaleFactor(scaleX, scaleY);
		//scaleY -= .5f;
		spriteCollection1->SetScaleFactor(scaleX, scaleY);
		break;
	case AZUL_KEY::KEY_EQUAL:
		scaleX += .5f;
		//testSprite->SetScaleFactor(scaleX, scaleY);
		//scaleY += .5f;
		spriteCollection1->SetScaleFactor(scaleX, scaleY);
		break;
	case AZUL_KEY::KEY_LEFT_BRACKET:
		if (animationDurationModifier > durationMin) {
			animationDurationModifier -= .25f;
			animatedSprite1->SetAnimationDurationModifier(animationDurationModifier);
			animatedSprite2->SetAnimationDurationModifier(animationDurationModifier);
		}

		break;
	case AZUL_KEY::KEY_RIGHT_BRACKET:
		if (animationDurationModifier < durationMax) {
			animationDurationModifier += .25f;
			animatedSprite1->SetAnimationDurationModifier(animationDurationModifier);
			animatedSprite2->SetAnimationDurationModifier(animationDurationModifier);
			animatedSprite1->SetCenter(1.f, -1.f);
		}

		break;
	}
}

void SpriteCollectionDemo::KeyDown(AZUL_KEY k)
{
	switch (k) {
	case AZUL_KEY::KEY_1:
		//testSprite->RotateByRadians(.05f);

		spriteCollection1->RotateByRadians(.05f);

		collectionViewer->SetPositionAbsolute(spriteCollection1->GetPosX(), spriteCollection1->GetPosY());
		collectionViewer->SetAngleRadians(spriteCollection1->GetAngleRadians());
		collectionViewer->SetScaleFactor(spriteCollection1->GetScaleX(), spriteCollection1->GetScaleY());
		collectionViewer->SetFlipX(spriteCollection1->GetFlipX());
		collectionViewer->SetFlipY(spriteCollection1->GetFlipY());
		break;
	case AZUL_KEY::KEY_2:
		spriteCollection1->RotateByRadians(-.05f);

		collectionViewer->SetPositionAbsolute(spriteCollection1->GetPosX(), spriteCollection1->GetPosY());
		collectionViewer->SetAngleRadians(spriteCollection1->GetAngleRadians());
		collectionViewer->SetScaleFactor(spriteCollection1->GetScaleX(), spriteCollection1->GetScaleY());
		collectionViewer->SetFlipX(spriteCollection1->GetFlipX());
		collectionViewer->SetFlipY(spriteCollection1->GetFlipY());
		break;
	case AZUL_KEY::KEY_3:
		//testSprite->SetCenter(-1.f,1.f);
		spriteCollection2->RotateByRadians(.05f);
		break;
	case AZUL_KEY::KEY_4:
		spriteCollection2->RotateByRadians(-.05f);
		break;
	case AZUL_KEY::KEY_5:
		spriteCollection3->RotateByRadians(.05f);
		break;
	case AZUL_KEY::KEY_6:
		spriteCollection3->RotateByRadians(-.05f);
		break;
	case AZUL_KEY::KEY_7:
		animatedSprite1->RotateByRadians(.05f);
		animatedSprite2->RotateByRadians(-.05f);
		break;
	case AZUL_KEY::KEY_8:
		animatedSprite1->RotateByRadians(-.05f);
		animatedSprite2->RotateByRadians(.05f);
		break;
	case AZUL_KEY::KEY_J:
		spriteCollection1->TransformPositionAbsolute(-2.f, 0.f);
		collectionViewer->SetPositionAbsolute(spriteCollection1->GetPosX(), spriteCollection1->GetPosY());
		collectionViewer->SetAngleRadians(spriteCollection1->GetAngleRadians());
		collectionViewer->SetScaleFactor(spriteCollection1->GetScaleX(), spriteCollection1->GetScaleY());
		collectionViewer->SetFlipX(spriteCollection1->GetFlipX());
		collectionViewer->SetFlipY(spriteCollection1->GetFlipY());
		break;
	case AZUL_KEY::KEY_K:
		spriteCollection1->TransformPositionAbsolute(0.f, -2.f);
		collectionViewer->SetPositionAbsolute(spriteCollection1->GetPosX(), spriteCollection1->GetPosY());
		collectionViewer->SetAngleRadians(spriteCollection1->GetAngleRadians());
		collectionViewer->SetScaleFactor(spriteCollection1->GetScaleX(), spriteCollection1->GetScaleY());
		collectionViewer->SetFlipX(spriteCollection1->GetFlipX());
		collectionViewer->SetFlipY(spriteCollection1->GetFlipY());
		break;
	case AZUL_KEY::KEY_L:
		spriteCollection1->TransformPositionAbsolute(2.f, 0.f);
		collectionViewer->SetPositionAbsolute(spriteCollection1->GetPosX(), spriteCollection1->GetPosY());
		collectionViewer->SetAngleRadians(spriteCollection1->GetAngleRadians());
		collectionViewer->SetScaleFactor(spriteCollection1->GetScaleX(), spriteCollection1->GetScaleY());
		collectionViewer->SetFlipX(spriteCollection1->GetFlipX());
		collectionViewer->SetFlipY(spriteCollection1->GetFlipY());
		break;
	case AZUL_KEY::KEY_I:
		spriteCollection1->TransformPositionAbsolute(0.f, 2.f);
		collectionViewer->SetPositionAbsolute(spriteCollection1->GetPosX(), spriteCollection1->GetPosY());
		collectionViewer->SetAngleRadians(spriteCollection1->GetAngleRadians());
		collectionViewer->SetScaleFactor(spriteCollection1->GetScaleX(), spriteCollection1->GetScaleY());
		collectionViewer->SetFlipX(spriteCollection1->GetFlipX());
		collectionViewer->SetFlipY(spriteCollection1->GetFlipY());
		break;
	}
}
