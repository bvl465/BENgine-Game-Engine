#include "BENgineSpriteAnimation.h"
#include "../BENgine.h"
#include "Image.h"
#include "../Asset Managers/Image Manager/ImageManager.h"
#include "../Asset Managers/Shader Manager/ShaderManager.h"
#include "../Asset Managers/Model Manager/ModelManager.h"

BENgineSpriteAnimation::BENgineSpriteAnimation(std::list<std::pair<std::string, float>> frameInfo) : numFrames(frameInfo.size())
{
	frameInfoArr = new FrameInfo *[numFrames];
	int i = 0;
	for (auto& frame : frameInfo)
	{
		Image* image = ImageManager::GetImage(frame.first);
		Rect* rect = image->pImageRect;
		frameInfoArr[i] = new FrameInfo(new GraphicsObject_Sprite(ModelManager::GetModel("UnitSquareXY"), ShaderManager::GetShaderObject("SpriteRender"), image, rect), frame.second);
		i++;
	}
	frameCenterArr = nullptr;
}


BENgineSpriteAnimation::BENgineSpriteAnimation(std::list<std::pair<std::string, float>> frameInfo, std::list<FrameCenter> frameCenter) : numFrames(frameInfo.size())
{
	int frameCenterSize = frameCenter.size();
	assert(numFrames == frameCenterSize);
	frameInfoArr = new FrameInfo * [numFrames];
	int i = 0;
	for (auto& frame : frameInfo)
	{
		Image* image = ImageManager::GetImage(frame.first);
		Rect* rect = image->pImageRect;
		frameInfoArr[i] = new FrameInfo(new GraphicsObject_Sprite(ModelManager::GetModel("UnitSquareXY"), ShaderManager::GetShaderObject("SpriteRender"), image, rect), frame.second);
		i++;
	}
	frameCenterArr = new FrameCenter * [numFrames];
	i = 0;
	for (auto& center : frameCenter)
	{
		frameCenterArr[i] = new FrameCenter(center.frameCenterX, center.frameCenterY);
		i++;
	}
}


// NOW INLINE FUNCTIONS

//int BENgineSpriteAnimation::GetNumFrames() const
//{
//	return numFrames;
//}

BENgineSpriteAnimation::FrameInfo* BENgineSpriteAnimation::GetFrameInfo(int index) const
{
	
	assert(index >= 0 && index < numFrames);
	return frameInfoArr[index];
}

FrameCenter* BENgineSpriteAnimation::GetFrameCenter(int index) const
{
	if (frameCenterArr != nullptr) {
		return frameCenterArr[index];
	}
	return nullptr;
}



BENgineSpriteAnimation::~BENgineSpriteAnimation()
{
	if (frameCenterArr == nullptr) {
		for (int i = 0; i < numFrames; i++)
		{
			delete frameInfoArr[i]->first;
			delete frameInfoArr[i];
		}
	}
	else {
		for (int i = 0; i < numFrames; i++)
		{
			delete frameCenterArr[i];
			delete frameInfoArr[i]->first;
			delete frameInfoArr[i];
		}
		delete frameCenterArr;
	}
	delete frameInfoArr;
}