#pragma once
#ifndef _Axis
#define _Axis
#include "../src/BENgine/Game Object/GameObject.h"
#include "../src/BENgine/Asset Managers/Shader Manager/ShaderManager.h"
#include "../src/BENgine/Asset Managers/Texture Manager/TextureManager.h"
#include "../src/BENgine/Asset Managers/Model Manager/ModelManager.h"
#include "../src/BENgine/Camera/CameraManager.h"
#include "../src/BENgine/BENgine.h"

class Axis : public GameObject
{
public:
	Axis();
	Axis(const Axis&) = delete;
	Axis& operator=(const Axis&) = delete;
	~Axis();
	virtual void Draw();
private:
	GraphicsObject_ColorNoTexture* pGObj_Axis;
};
#endif _Axis