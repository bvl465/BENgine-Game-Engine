//Ben La Monica
#include "Bullet.h"
#include "Enemy.h"
#include "SceneTest.h"
#include "../src/BENgine/Scene/SceneManager.h"
#include "../src/BENgine/Scene/Scene.h"
#include "../src/BENgine/Visualizer/Visualizer.h"
#include "BulletPool.h"
#include "../src/BENgine/Terrain/TerrainObject.h"
Bullet::Bullet()
{
	pGObj_BulletLight = new GraphicsObject_TextureLight(ModelManager::GetModel("pModelSpaceFrigate"), ShaderManager::GetShaderObject("pShaderObject_textureLight"), TextureManager::GetTexture("pSpaceFrigateTex"), LightColor, LightPos);

	ShipScale.set(SCALE, 0.01f, 0.01f, 0.01f);
	ShipRotTrans = Matrix(ROT_Y, 0) * Matrix(TRANS, 0, 20, 0);
	Matrix world = ShipScale * ShipRotTrans;
	pGObj_BulletLight->SetWorld(world);
	SetColliderModel(pGObj_BulletLight->getModel(), VolumeType::BSphere);

}

Bullet::~Bullet()
{
	delete pGObj_BulletLight;
}

void Bullet::Initialize(Matrix rotTans, BulletPool* bp)
{
	ShipRotTrans = rotTans;
	Matrix world = ShipScale * ShipRotTrans;
	pGObj_BulletLight->SetWorld(world);
	pBulletPool = bp;
	SetColliderModel(pGObj_BulletLight->getModel(), VolumeType::BSphere);
	SubmitEntry();
}

void Bullet::Alarm0()
{
	DebugMsg::out("Bullet Lifetime Limit Reached\n");
	alarmActive = false;
	SubmitExit();
}

void Bullet::Update()
{

	// Spaceship adjust matrix
	ShipRotTrans = Matrix(TRANS, Vect(0, 0, bulletSpeed)) * ShipRotTrans;
	Matrix world = ShipScale * ShipRotTrans;
	pGObj_BulletLight->SetWorld(world);
	this->UpdateCollisionData(world);

	// Toggle the bounding sphere's visibility
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_SPACE))
	{
		if (collisionTrue)
		{
			GetCollisionVolume().DebugView(Red);
		}
		else
		{
			GetCollisionVolume().DebugView(Blue);
		}
	}
	else
	{
		//Visualizer::ShowBSphere(this->GetBSphere(), Blue);
		BsphereToggle = false;
		//DebugMsg::out("Bounding sphere: Off\n");
	}
	TerrainObject* terrain = SceneManager::GetCurrentScene()->GetTerrainManager()->GetCurrentTerrain();
	terrain->Intersect(this);
	collisionTrue = false;
}

void Bullet::Draw()
{
	pGObj_BulletLight->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());
}

void Bullet::SceneEntry()
{
	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, duration);
	SetCollidableGroup<Bullet>();
	SubmitCollisionRegistration();

	SetColliderModel(pGObj_BulletLight->getModel(), VolumeType::BSphere);
	Matrix world = ShipScale * ShipRotTrans;
	UpdateCollisionData(world);
	alarmActive = true;
}

void Bullet::SceneExit()
{
	if (alarmActive == true) {
		SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);
	}
	//SubmitAlarmDeregistration(AlarmableManager::ALARM_ID::ALARM_0);
	SubmitCollisionDeregistration();
	SubmitDrawDeregistration();
	SubmitUpdateDeregistration();
	pBulletPool->ReturnBullet(this);

}


void Bullet::Collision(Enemy*)
{
	this->collisionTrue = true;
	SubmitExit();

}

void Bullet::CollisionTerrain()
{
	this->collisionTrue = true;
	SubmitExit();
}
