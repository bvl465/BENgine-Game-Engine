#pragma once
#ifndef _StitchSprite
#define _StitchSprite
#include "../src/BENgine/Game Object/GameObject.h"
//#include "../src/BENgine/Asset Managers/Model Manager/ModelManager.h"
//#include "../src/BENgine/Asset Managers/Texture Manager/TextureManager.h"
//#include "../src/BENgine/Asset Managers/Shader Manager/ShaderManager.h"
//#include "../src/BENgine/Camera/CameraManager.h"
//#include "../src/BENgine/BENgine.h"
class BENgineSprite;
class StitchSprite : public GameObject
{
public:
	StitchSprite();
	StitchSprite(const StitchSprite&) = delete;
	StitchSprite& operator=(const StitchSprite&) = delete;
	~StitchSprite();
	virtual void Update();

private:
	BENgineSprite* stitch;
};
#endif _StitchSprite