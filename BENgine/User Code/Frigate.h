#pragma once
#ifndef _Frigate
#define _Frigate
#include "../src/BENgine/Game Object/GameObject.h"
class SpriteFont;
class BulletPool;
class Enemy;
class SpriteString;
class Frigate : public GameObject
{
public:
	Frigate();
	Frigate(const Frigate&) = delete;
	Frigate& operator=(const Frigate&) = delete;
	~Frigate();
	virtual void Alarm0() override;
	virtual void Alarm1() override;
	virtual void Alarm2() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Draw2D() override;
	virtual void KeyPress(AZUL_KEY k) override;

	virtual void KeyDown(AZUL_KEY k) override;

	void IgnoreKeyPress();
	void Collision(Frigate*);//{// DebugMsg::out("Collision with frigate \n"); }
	void Collision(Enemy*);//{// DebugMsg::out("Collision with frigate \n"); }
	
private:

	Matrix ShipScale;
	Matrix ShipRotTrans;
	

	Vect LightColor = Vect(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos = Vect(1.0f, 1.0f, 1.0f, 1.0f);
	GraphicsObject_TextureLight* pGObj_SpaceFrigateLight;
	float ShipTransSpeed = 2.125f;
	const float ShipTransSpeedFast = 2.125f;
	const float ShipTransSpeedSlow = .05125f;
	const float ShipRotAng = .05f;
	bool collisionTrue = false;
	bool drawRegistered = true;
	bool ignoreKeyPress = false;
	BulletPool* pBulletPool = nullptr;
	SpriteFont* pSpriteFont = nullptr;
	std::string message = "Bullets Fired: 0";
	int bulletsFired = 0;
	SpriteString* pSpriteString = nullptr;
	//bool canShoot = true;
	//const float shootRechargeTime = 1.f;
	const Vect bulletOffset = Vect(0.f, 1.f, 1.f);

};
#endif _Frigate