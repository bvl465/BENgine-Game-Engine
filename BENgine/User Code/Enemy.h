#pragma once
#ifndef _Enemy
#define _Enemy
#include "../src/BENgine/Game Object/GameObject.h"
#include "../src/BENgine/Asset Managers/Model Manager/ModelManager.h"
#include "../src/BENgine/Asset Managers/Texture Manager/TextureManager.h"
#include "../src/BENgine/Asset Managers/Shader Manager/ShaderManager.h"
#include "../src/BENgine/Camera/CameraManager.h"
#include "../src/BENgine/BENgine.h"
class Bullet;
class Frigate;
class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(const Enemy&) = delete;
	Enemy& operator=(const Enemy&) = delete;
	~Enemy();
	virtual void Update();
	virtual void Draw();

	void SetWorld(Matrix world);
	void Collision(Frigate*);//{// DebugMsg::out("Collision with frigate \n"); }
	void Collision(Enemy*);//{// DebugMsg::out("Collision with frigate \n"); }
	void Collision(Bullet*);//{// DebugMsg::out("Collision with frigate \n"); }
private:

	//GraphicsObject_WireframeConstantColor* pGObj_SpaceshipBSphere;
	Matrix ShipScale;
	Matrix ShipRotTrans;


	Vect LightColor = Vect(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos = Vect(1.0f, 1.0f, 1.0f, 1.0f);
	Vect Blue = Vect(0.0f, 0.0f, 1.0f, 1.0f);
	Vect Red = Vect(1.0f, 0.0f, 0.0f, 1.0f);

	GraphicsObject_TextureLight* pGObj_CottageLight;

	bool collisionTrue = false;
	bool BsphereToggle = false;
	bool ignoreKeyPress = false;
};
#endif _Enemy