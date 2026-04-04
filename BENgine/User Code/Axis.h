#pragma once
#ifndef _Axis
#define _Axis
#include "../src/BENgine/Game Object/GameObject.h"


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