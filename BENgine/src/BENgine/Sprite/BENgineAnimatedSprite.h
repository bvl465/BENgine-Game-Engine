#ifndef _BENgineAnimatedSprite
#define _BENgineAnimatedSprite

#include "AzulCore.h"
#include "BENgineSprite.h"
class BENgineSpriteAnimation;
class BENgineSpriteAnimationCommandLoop;
class Camera;

//BENgineAnimatedSprite is a BENgineSprite that can make use of BENgineSpriteAnimations to swap the GraphicsObject_Sprite
//Important note:
//Unlike BENgineSprite, BENgineAnimatedSprite does NOT delete the GraphicsObject_Sprite it uses. This is because the GraphicsObject_Sprite 
//is owned by the BENgineSpriteAnimation and is shared between all BENgineAnimatedSprites that use the same BENgineSpriteAnimation.
class BENgineAnimatedSprite : public BENgineSprite
{
public:

	enum class FrameCenteringSetting
	{
		//Uses the center defined by the user
		IGNORE_ANIMATION_CENTER,

		//Use the center defined by the BENgineSpriteAnimation
		USE_ANIMATION_CENTER
	};


    BENgineAnimatedSprite() = delete;
    BENgineAnimatedSprite(const BENgineAnimatedSprite&) = delete;
    BENgineAnimatedSprite& operator=(const BENgineAnimatedSprite&) = delete;
    ~BENgineAnimatedSprite();

    BENgineAnimatedSprite(BENgineSpriteAnimation* animation);
    BENgineAnimatedSprite(BENgineSpriteAnimation* animation, SpriteAutoUpdateWorldSetting spriteAutoWorldUpdateSetting);

	//SHOULD BE PRIVATE ----------------------------------------------------------------------------------------------------
	
	//This function is called by the animation command loop to advance the animation. It is not meant to be called directly.
	void ExecuteLoop(GraphicsObject_Sprite* graphicsObjectSprite);

	//----------------------------------------------------------------------------------------------------------------------

	//Sets the current frame of the animation.
	//Parameters:
	//frame - the frame number to set the animation to.
    void SetFrame(int frame);

	//Sets the GraphicsObject_Sprite of the animated sprite.
    //It does not alter the BENgineSpriteAnimation that the animated sprite is using.
    void SetGraphicObjectSprite(GraphicsObject_Sprite* graphicsObjectSprite);

	//Advances the animation to the next frame. If the animation is at the last frame it will loop back to the first frame.
	void AdvanceFrame();

	//Starts a loop of the animation from the frame number passed in. If the animation is already looping it will reset the loop to start from the new frame number.
	//Parameters:
	//frame - the frame number to start the loop from.
	void LoopAnimationFromFrame(int frame);

    //Stops the animation loop at its current frame
    void CancelAnimation();

	//Sets the duration modifer of the sprite to use on the animation. A value of 1 is normal speed, less than 1 is slower, and greater than 1 is faster.
	//Parameters:
	//modifier - the duration modifier to set for this sprite.
	void SetAnimationDurationModifier(float modifier);

	FrameCenteringSetting GetFrameCenteringSetting();


	void SetFrameCenteringSetting(FrameCenteringSetting frameCenteringSetting);



	//Returns the mumber of the current frame of the animation
    int GetCurrentFrame() const;
	
	//Sets the animation of the animated sprite. This will reset the current frame to 0 and stop any current animation loop.
	//Parameters:
	//animation - a pointer to the BENgineSpriteAnimation to set for this animated sprite.
	void SetAnimation(BENgineSpriteAnimation* animation);

	//Sets the animation of the animated sprite and the current frame of the animation. This will stop any current animation loop.
	//Parameters:
	//animation - a pointer to the BENgineSpriteAnimation to set for this animated sprite.
	//frame - the frame number to set the current frame to.
	void SetAnimationAndFrame(BENgineSpriteAnimation* animation, int frame);

private:

    void PrepGraphicsObject();

	//The animation that the animated sprite is using.
    BENgineSpriteAnimation* ptrSpriteAnimation;

	//Modifier for the duration of each frame of the animation. A value of 1 is normal speed, less than 1 is slower, and greater than 1 is faster.
	float durationModifier;

	//Current frame of the animation
    int currentFrame;

	//Command object for the animation
	BENgineSpriteAnimationCommandLoop* ptrAnimationCommandLoop;

	FrameCenteringSetting centeringSetting;

	// animationCommandIterator; //iterator for the animation command list
};

//TODO make ExecuteLoop private

#endif _BENgineAnimatedSprite