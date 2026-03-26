#pragma once
#ifndef _Bullet
#define _Bullet
#include "../src/BENgine/Game Object/GameObject.h"
#include "../src/BENgine/Asset Managers/Model Manager/ModelManager.h"
#include "../src/BENgine/Asset Managers/Texture Manager/TextureManager.h"
#include "../src/BENgine/Asset Managers/Shader Manager/ShaderManager.h"
#include "../src/BENgine/Camera/CameraManager.h"
#include "../src/BENgine/BENgine.h"

class Frigate;
class BulletPool;
class Enemy;
class Bullet : public GameObject
{
public:
	Bullet();
	Bullet(const Bullet&) = delete;
	Bullet& operator=(const Bullet&) = delete;
	~Bullet();
	void Initialize(Matrix rotTrans, BulletPool* bp);
	virtual void Alarm0();
	virtual void Update();
	virtual void Draw();
	void SceneEntry() override;
	void SceneExit() override;
	void Collision(Enemy*);//{// DebugMsg::out("Collision with frigate \n"); }
	void CollisionTerrain();//{// DebugMsg::out("Collision with terrain \n"); }
private:

	//GraphicsObject_WireframeConstantColor* pGObj_SpaceshipBSphere;
	Matrix ShipScale;
	Matrix ShipRotTrans;


	Vect LightColor = Vect(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos = Vect(1.0f, 1.0f, 1.0f, 1.0f);
	Vect Blue = Vect(0.0f, 0.0f, 1.0f, 1.0f);
	Vect Red = Vect(1.0f, 0.0f, 0.0f, 1.0f);
	GraphicsObject_TextureLight* pGObj_BulletLight;
	const float bulletSpeed = 1.f;
	const float duration = 3.f;
	bool collisionTrue = false;
	bool BsphereToggle = false;
	BulletPool* pBulletPool = nullptr;
	bool alarmActive = false;
	
	//bool canShoot = true;
	//const float shootRechargeTime = 1.f;
	//const Vect bulletOffset = Vect(0.f, 1.f, 1.f);

};
#endif _Bullet