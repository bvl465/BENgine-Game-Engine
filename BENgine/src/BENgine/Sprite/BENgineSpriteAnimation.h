#ifndef _BENgineSpriteAnimation
#define _BENgineSpriteAnimation

#include "AzulCore.h"
#include <list>

class Camera;

struct FrameCenter {
    float frameCenterX;
    float frameCenterY;
    FrameCenter(float centerX, float centerY) : frameCenterX(centerX), frameCenterY(centerY){}
};

class BENgineSpriteAnimation
{
public:
	using FrameInfo = std::pair<GraphicsObject_Sprite*, float>;
    
    BENgineSpriteAnimation() = default;
    BENgineSpriteAnimation(const BENgineSpriteAnimation&) = delete;
    BENgineSpriteAnimation& operator=(const BENgineSpriteAnimation&) = delete;

	//Deletes the GraphicsObject_Sprite objects in the frameInfoArr and the frameInfoArr itself.
    ~BENgineSpriteAnimation();

	//Constructor that takes a list of pairs, where each pair consists of the key of the Image in the ImageManager to create a GraphicsObject_Sprite from and a float representing the duration of that frame in seconds. The order of the frames in the list determines the order of the animation.
    //Parameters:
	//frameInfo - list of pairs to construct the frameInfoArr from.
    BENgineSpriteAnimation(std::list<std::pair<std::string, float>> frameInfo);

    //Constructor that takes a list of pairs, where each pair consists of the key of the Image in the ImageManager to create a GraphicsObject_Sprite from and a float representing the duration of that frame in seconds. The order of the frames in the list determines the order of the animation.
    //It also takes a list of FrameCenters that correspond to the frames in frameInfo. The number of items in frameInfo and frameCenter must be the same.
    //Parameters:
    //frameInfo - list of pairs to construct the frameInfoArr from.
    //frameCenter - list of FrameCenter that defines the center point of the frames in frameInfo
    BENgineSpriteAnimation(std::list<std::pair<std::string, float>> frameInfo, std::list<FrameCenter> frameCenter);

    
    //Returns the number of frames in the animation
    int GetNumFrames() const {
        return numFrames;
    };
    
	//Gets the frame info at the specified index of the animation.
    //Parameters:
	//index - The index of the frame info to retrieve. Must be between 0 and GetNumFrames() - 1.
	FrameInfo* GetFrameInfo(int index) const;

    //Gets the FrameCenter at the specified index of the animation
    //Parameters:
    //index - The index of the FrameCenter to retrieve. Must be between 0 and GetNumFrames() - 1
    FrameCenter* GetFrameCenter(int index) const;
    
private:
    const int numFrames;
    FrameInfo** frameInfoArr = nullptr;
    FrameCenter** frameCenterArr = nullptr;

};

#endif _BENgineSpriteAnimation