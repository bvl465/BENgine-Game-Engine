#pragma once
#ifndef _AnimatedSpriteDemo
#define _AnimatedSpriteDemo
#include "../src/BENgine/Game Object/GameObject.h"
#include "../src/BENgine/Asset Managers/Model Manager/ModelManager.h"
#include "../src/BENgine/Asset Managers/Texture Manager/TextureManager.h"
#include "../src/BENgine/Asset Managers/Shader Manager/ShaderManager.h"
#include "../src/BENgine/Camera/CameraManager.h"
#include "../src/BENgine/BENgine.h"
class BENgineAnimatedSprite;
class BENgineSpriteAnimation;
class AnimatedSpriteDemo : public GameObject
{
public:
	AnimatedSpriteDemo();
	AnimatedSpriteDemo(const AnimatedSpriteDemo&) = delete;
	AnimatedSpriteDemo& operator=(const AnimatedSpriteDemo&) = delete;
	~AnimatedSpriteDemo();
	virtual void Update();

	virtual void Draw2D() override;

private:
	int framesBeforeRotation = 300;
	BENgineAnimatedSprite* animatedSprite;
	BENgineSpriteAnimation* animation1;
	BENgineSpriteAnimation* animation2;
	
};
#endif _AnimatedSpriteDemo