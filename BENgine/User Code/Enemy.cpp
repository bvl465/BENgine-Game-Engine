//Ben La Monica
#include "Enemy.h"
#include "Frigate.h"
#include "Bullet.h"
#include "SceneTest.h"
#include "EnemyPool.h"
#include "../src/BENgine/Scene/SceneManager.h"
#include "../src/BENgine/Scene/Scene.h"
#include "../src/BENgine/Visualizer/Visualizer.h"

Enemy::Enemy()
{
	pGObj_CottageLight = new GraphicsObject_TextureLight(ModelManager::GetModel("pModelCottage"), ShaderManager::GetShaderObject("pShaderObject_textureLight"), TextureManager::GetTexture("pCottageTexture"), LightColor, LightPos);



	ShipScale.set(SCALE, 1.f, 1.f, 1.f);
	ShipRotTrans = Matrix(ROT_Y, 0) * Matrix(TRANS, 0, 20, 20);
	Matrix world = ShipScale * ShipRotTrans;
	pGObj_CottageLight->SetWorld(world);


	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	SetCollidableGroup<Enemy>();
	SubmitCollisionRegistration();

	SetColliderModel(pGObj_CottageLight->getModel(), VolumeType::AABB);
	UpdateCollisionData(world);
}

Enemy::~Enemy()
{
	Updatable::SubmitUpdateDeregistration();

	Drawable::SubmitDrawDeregistration();

	SubmitCollisionDeregistration();
	delete pGObj_CottageLight;
}


void Enemy::Update()
{


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
	collisionTrue = false;

}


void Enemy::Draw()
{
	pGObj_CottageLight->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());

	//if (BsphereToggle)
	//{
	//	pGObj_SpaceshipBSphere->Render(CameraManager::GetCurrentCamera());
	//}


}



void Enemy::SetWorld(Matrix world)
{
	pGObj_CottageLight->SetWorld(world);
	UpdateCollisionData(world);
}

void Enemy::Collision(Frigate*)
{
	collisionTrue = true;
}
void Enemy::Collision(Enemy*)
{
	collisionTrue = true;
}

void Enemy::Collision(Bullet*)
{
	collisionTrue = true;
}
