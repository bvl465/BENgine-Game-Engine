#include "BENgineSpriteAnimationCommandLoop.h"
#include "BENgineAnimatedSprite.h"
#include "../Scene/SceneAttorney.h"
#include "../Scene/SceneManager.h"


void BENgineSpriteAnimationCommandLoop::Execute()
{
	animatedSprite->ExecuteLoop(ptrGOSprite);
}


BENgineSpriteAnimationCommandLoop::BENgineSpriteAnimationCommandLoop(BENgineAnimatedSprite* sprite)
{
	animatedSprite = sprite;
}
