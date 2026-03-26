#include "BENgineAnimatedSprite.h"
#include "BENgineSpriteAnimation.h"
#include "BENgineSpriteAnimationCommandLoop.h"
#include "../BENgine.h"
#include "Image.h"
#include "../Asset Managers/Image Manager/ImageManager.h"
#include "../Asset Managers/Shader Manager/ShaderManager.h"
#include "../Asset Managers/Model Manager/ModelManager.h"

BENgineAnimatedSprite::BENgineAnimatedSprite(BENgineSpriteAnimation* animation) : ptrSpriteAnimation(animation), durationModifier(1.f), currentFrame(0), centeringSetting(FrameCenteringSetting::IGNORE_ANIMATION_CENTER)
{
	assert(animation != nullptr);
	assert(animation->GetNumFrames() > 0);
	ptrGOSprite = (ptrSpriteAnimation->GetFrameInfo(0))->first;
	ptrAnimationCommandLoop = new BENgineSpriteAnimationCommandLoop(this);

	//Values set from inheritance
	//scaleX = 1.f;
	//scaleY = 1.f;
	//angle = 0.f;
	//cosAngle = 1.f;
	//sinAngle = 0.f;
	//centerX = 0.f;
	//centerY = 0.f;

	offsetX = -ptrGOSprite->origPosX;
	offsetY = -ptrGOSprite->origPosY;
	posX = ptrGOSprite->origPosX * .5f * ptrGOSprite->origWidth;
	posY = ptrGOSprite->origPosY * .5f * ptrGOSprite->origHeight;
	UpdateWorld();
}

BENgineAnimatedSprite::BENgineAnimatedSprite(BENgineSpriteAnimation* animation, SpriteAutoUpdateWorldSetting spriteAutoWorldUpdateSetting) : ptrSpriteAnimation(animation), durationModifier(1.f), currentFrame(0), centeringSetting(FrameCenteringSetting::IGNORE_ANIMATION_CENTER)
{
	assert(animation != nullptr);
	assert(animation->GetNumFrames() > 0);
	updateWorldSetting = spriteAutoWorldUpdateSetting;
	ptrGOSprite = (ptrSpriteAnimation->GetFrameInfo(0))->first;
	ptrAnimationCommandLoop = new BENgineSpriteAnimationCommandLoop(this);

	//Values set from inheritance
	//scaleX = 1.f;
	//scaleY = 1.f;
	//angle = 0.f;
	//cosAngle = 1.f;
	//sinAngle = 0.f;
	//centerX = 0.f;
	//centerY = 0.f;

	offsetX = -ptrGOSprite->origPosX;
	offsetY = -ptrGOSprite->origPosY;
	posX = ptrGOSprite->origPosX * .5f * ptrGOSprite->origWidth;
	posY = ptrGOSprite->origPosY * .5f * ptrGOSprite->origHeight;

	updateWorldSetting = spriteAutoWorldUpdateSetting;
	UpdateWorld();
}


void BENgineAnimatedSprite::SetFrame(int frame)
{
	assert(frame < ptrSpriteAnimation->GetNumFrames() && frame >= 0);
	ptrGOSprite = (ptrSpriteAnimation->GetFrameInfo(frame))->first;
	//Adjust center to match if it were changed
	PrepGraphicsObject();
}

void BENgineAnimatedSprite::SetGraphicObjectSprite(GraphicsObject_Sprite* graphicsObjectSprite)
{
	ptrGOSprite = graphicsObjectSprite;
	PrepGraphicsObject();
}

void BENgineAnimatedSprite::AdvanceFrame()
{
	if (currentFrame >= ptrSpriteAnimation->GetNumFrames())
	{
		currentFrame = 0;
	}
	else {
		currentFrame++;
	}
	ptrGOSprite = (ptrSpriteAnimation->GetFrameInfo(currentFrame))->first;
	PrepGraphicsObject();
}

void BENgineAnimatedSprite::LoopAnimationFromFrame(int frame)
{
	assert(frame < ptrSpriteAnimation->GetNumFrames() && frame >= 0);
	ptrGOSprite = (ptrSpriteAnimation->GetFrameInfo(frame))->first;
	PrepGraphicsObject();
	currentFrame = frame;
	frame += 1;
	if (frame >= ptrSpriteAnimation->GetNumFrames())
	{
		frame = 0;
	}
	ptrAnimationCommandLoop->AddToTimer((ptrSpriteAnimation->GetFrameInfo(frame))->first , ptrSpriteAnimation->GetFrameInfo(currentFrame)->second);
}

void BENgineAnimatedSprite::CancelAnimation()
{
	ptrAnimationCommandLoop->RemoveFromTimer();
}

void BENgineAnimatedSprite::SetAnimationDurationModifier(float modifier)
{
	durationModifier = modifier;
}

BENgineAnimatedSprite::FrameCenteringSetting BENgineAnimatedSprite::GetFrameCenteringSetting()
{
	return centeringSetting;
}

void BENgineAnimatedSprite::SetFrameCenteringSetting(FrameCenteringSetting frameCenteringSetting)
{
	centeringSetting = frameCenteringSetting;
}

void BENgineAnimatedSprite::ExecuteLoop(GraphicsObject_Sprite* graphicsObjectSprite)
{
	ptrGOSprite = graphicsObjectSprite;

	//ptrAnimationCommandLoop->AddToTimer(ptrGOSprite, ptrSpriteAnimation->GetFrameInfo(frame)->second * animationSpeed);
	currentFrame++;
	if (currentFrame >= ptrSpriteAnimation->GetNumFrames())
	{
		currentFrame = 0;
	}
	int nextFrame = currentFrame + 1;
	if (nextFrame >= ptrSpriteAnimation->GetNumFrames())
	{
		nextFrame = 0;
	}
	PrepGraphicsObject();
	ptrAnimationCommandLoop->AddToTimer(ptrSpriteAnimation->GetFrameInfo(nextFrame)->first, ptrSpriteAnimation->GetFrameInfo(currentFrame)->second * durationModifier);
	//ptrAnimationCommandLoop->SetFrame(graphicsObjectSprite);
	//ptrAnimationCommandLoop->AddToTimer(graphicsObjectSprite, ptrSpriteAnimation->GetFrameInfo(graphicsObjectSprite)->second * animationSpeed);
}

int BENgineAnimatedSprite::GetCurrentFrame() const
{
	return currentFrame;
}

void BENgineAnimatedSprite::SetAnimation(BENgineSpriteAnimation* animation)
{
	assert(animation != nullptr);
	assert(animation->GetNumFrames() > 0);
	ptrAnimationCommandLoop->RemoveFromTimer();
	ptrSpriteAnimation = animation;
	ptrGOSprite = (ptrSpriteAnimation->GetFrameInfo(0))->first;
	PrepGraphicsObject();
	currentFrame = 0;
}

void BENgineAnimatedSprite::SetAnimationAndFrame(BENgineSpriteAnimation* animation, int frame)
{
	assert(animation != nullptr);
	assert(animation->GetNumFrames() > 0);
	assert(frame < animation->GetNumFrames() && frame >= 0);
	ptrAnimationCommandLoop->RemoveFromTimer();
	ptrSpriteAnimation = animation;
	currentFrame = frame;
	ptrGOSprite = (ptrSpriteAnimation->GetFrameInfo(currentFrame))->first;
	PrepGraphicsObject();

}


void BENgineAnimatedSprite::PrepGraphicsObject()
{
	//ptrGOSprite->origPosX = centerX * ((ptrGOSprite->origWidth) * .5f);
	//ptrGOSprite->origPosY = centerY * ((ptrGOSprite->origHeight) * .5f);
	//offsetX = -ptrGOSprite->origPosX;
	//offsetY = -ptrGOSprite->origPosY;

	//if (centeringSetting == FrameCenteringSetting::IGNORE_ANIMATION_CENTER) {
	//	offsetX = -centerX * ((ptrGOSprite->origWidth) * .5f);
	//	offsetY = -centerY * ((ptrGOSprite->origHeight) * .5f);
	//}
	//else {
	//	FrameCenter* currentFrameCenter = ptrSpriteAnimation->GetFrameCenter(currentFrame);
	//	centerX = currentFrameCenter->frameCenterX;
	//	centerY = currentFrameCenter->frameCenterY;
	//	offsetX = -centerX * ((ptrGOSprite->origWidth) * .5f);
	//	offsetY = -centerY * ((ptrGOSprite->origHeight) * .5f);
	//}


	if (centeringSetting == FrameCenteringSetting::USE_ANIMATION_CENTER) {
		FrameCenter* currentFrameCenter = ptrSpriteAnimation->GetFrameCenter(currentFrame);
		//Will crash if the animation has no frameCenterArr
		centerX = currentFrameCenter->frameCenterX;
		centerY = currentFrameCenter->frameCenterY;
	}
	offsetX = -centerX * ((ptrGOSprite->origWidth) * .5f);
	offsetY = -centerY * ((ptrGOSprite->origHeight) * .5f);

	UpdateWorld();
}


BENgineAnimatedSprite::~BENgineAnimatedSprite()
{
	ptrGOSprite = nullptr;
	delete ptrAnimationCommandLoop;
}

