#pragma once
#ifndef _WorldPlane
#define _WorldPlane
#include "../src/BENgine/Game Object/GameObject.h"
#include "../src/BENgine/BENgine.h"
class GraphicsObject_TextureFlat;
class Terrain;
class WorldPlane : public GameObject
{
public:
	//Basic world plane with grid texture
	WorldPlane();
	WorldPlane(const WorldPlane&) = delete;
	WorldPlane& operator=(const WorldPlane&) = delete;
	~WorldPlane();

	virtual void Draw();
private:
	GraphicsObject_TextureFlat* pGObj_WorldPlane;
};
#endif _WorldPlane