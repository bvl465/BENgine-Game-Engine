//Ben La Monica
#include "Frigate.h"
#include "Enemy.h"
#include "SceneTest.h"
#include "FlightScene.h"
#include "SceneDemo.h"
#include "../src/BENgine/Scene/SceneManager.h"
#include "../src/BENgine/Scene/Scene.h"
#include "../src/BENgine/Visualizer/Visualizer.h"
#include "BulletPool.h"
#include "Bullet.h"
#include "../src/BENgine/Sprite/SpriteFontManager.h"
#include "../src/BENgine/Collision/CollisionVolumeBSphere.h"
#include "../src/BENgine/Utilities/DefaultColors.h"
#include "../src/BENgine/Terrain/TerrainObject.h"
#include "../src/BENgine/Sprite/SpriteFont.h"
#include "../src/BENgine/Sprite/SpriteString.h"

Frigate::Frigate()
{

	pGObj_SpaceFrigateLight = new GraphicsObject_TextureLight(ModelManager::GetModel("pModelXWing"), ShaderManager::GetShaderObject("pShaderObject_textureLight"), TextureManager::GetTexture("pXWingTexture"), LightColor, LightPos);



	ShipScale.set(SCALE, 1.f, 1.f, 1.f);
	ShipRotTrans = Matrix(ROT_Y, 0) * Matrix(TRANS, 0, 20, 0);
	Matrix world = ShipScale * ShipRotTrans;
	pGObj_SpaceFrigateLight->SetWorld(world);
	pBulletPool = new BulletPool();

	Updatable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 5.f);
	SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_1, 11.f);
	SubmitKeyRegistration(AZUL_KEY::KEY_J, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_U, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_O, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_L, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_K, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_I, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_B, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_J, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_L, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_K, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_I, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_X, KeyEvent::KEY_PRESSED);
	SetCollidableGroup<Frigate>();
	SubmitCollisionRegistration();

	SetColliderModel(pGObj_SpaceFrigateLight->getModel(), VolumeType::OBB);
	UpdateCollisionData(world);


	pSpriteFont = SpriteFontManager::GetSpriteFont("pCourierNew");

	pSpriteString = new SpriteString("pCourierNew", message, SpriteString::PositionType::Absolute, 300.f, 300.f, SpriteString::Alignment::Left);

}

Frigate::~Frigate()
{

	Updatable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	delete pSpriteString;
	SubmitKeyDeregistration(AZUL_KEY::KEY_J, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_U, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_O, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_L, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_K, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_I, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_B, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_J, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_L, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_K, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_I, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_X, KeyEvent::KEY_PRESSED);
	SubmitCollisionDeregistration();
	delete pGObj_SpaceFrigateLight;
	delete pBulletPool;
	
}

void Frigate::Alarm0()
{
	//DebugMsg::out("I AM ALARM 0!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	//Drawable::SubmitDrawDeregistration();
	//drawRegistered = false;
	SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_2, 5.f);
}

void Frigate::Alarm1()
{
	//DebugMsg::out("I AM ALARM 1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
}



void Frigate::Alarm2()
{
	//Drawable::SubmitDrawRegistration();
	//drawRegistered = true;
	//DebugMsg::out("I AM ALARM 2!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	SubmitAlarmRegistration(AlarmableManager::ALARM_ID::ALARM_0, 5.f);
}

void Frigate::Update()
{

	// Spaceship adjust matrix
	SceneManager::GetCurrentScene()->GetTerrainManager()->GetCurrentTerrain()->ShowCell(Vect(ShipRotTrans.M12(), ShipRotTrans.M13(), ShipRotTrans.M14()));
	float height = SceneManager::GetCurrentScene()->GetTerrainManager()->GetCurrentTerrain()->GetTerrainObjectHeight(Vect(ShipRotTrans.M12(), ShipRotTrans.M13(), ShipRotTrans.M14()));
	//ShipRotTrans.M13() = terrain->GetTerrainHeight(Vect(ShipRotTrans.M12(), ShipRotTrans.M13(), ShipRotTrans.M14())) + 10.f;
	Vect norm = SceneManager::GetCurrentScene()->GetTerrainManager()->GetCurrentTerrain()->GetTerrainObjectNormal(Vect(ShipRotTrans.M12(), ShipRotTrans.M13(), ShipRotTrans.M14()));
	ShipRotTrans.M13() = height + 10.f; // Set the height of the ship to be above the terrain
	
	Visualizer::ShowVectorFromPoint(Vect(ShipRotTrans.M12(), height, ShipRotTrans.M14()), norm * 10.f, Colors::Plum, .05f);

	Vect r = norm.cross(ShipRotTrans.get(ROW_2));
	Vect fwd = r.cross(norm);
	
	ShipRotTrans = Matrix(ROT_ORIENT, fwd, norm) * Matrix(TRANS, ShipRotTrans.get(ROW_3));
	Matrix world = ShipScale * ShipRotTrans;
	pGObj_SpaceFrigateLight->SetWorld(world);
	this->UpdateCollisionData(world);


	// Toggle the bounding sphere's visibility
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_SPACE))
	{
		if (collisionTrue)
		{
			//GetCollisionVolume().DebugView(Colors::Red);
			//GetBSphere().DebugView(Colors::Red);
			Visualizer::ShowBSphere(this->GetBSphere(), Colors::Red);
		}
		else
		{
			//GetCollisionVolume().DebugView(Colors::Blue);
			//GetBSphere().DebugView(Colors::Blue);
			Visualizer::ShowBSphere(this->GetBSphere(), Colors::Blue);
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

void Frigate::Draw()
{
	pGObj_SpaceFrigateLight->Render(SceneManager::GetCurrentScene()->GetCurrentCamera());

}

void Frigate::Draw2D()
{
	pSpriteString->Render(SceneManager::GetCurrentScene()->GetCurrentCamera2D());
}

void Frigate::KeyPress(AZUL_KEY k)
{
	if (!ignoreKeyPress) {
		switch (k) {
		case AZUL_KEY::KEY_J:
			ShipRotTrans = Matrix(ROT_Y, ShipRotAng) * ShipRotTrans;
			break;
		case AZUL_KEY::KEY_U:
			ShipTransSpeed = ShipTransSpeedFast;
			break;
		case AZUL_KEY::KEY_O:
			ShipTransSpeed = ShipTransSpeedSlow;
			break;
		case AZUL_KEY::KEY_I:
			ShipRotTrans = Matrix(TRANS, Vect(0, 0, ShipTransSpeed)) * ShipRotTrans;
			break;
		case AZUL_KEY::KEY_K:
			ShipRotTrans = Matrix(TRANS, Vect(0, 0, -ShipTransSpeed)) * ShipRotTrans;
			break;
		case AZUL_KEY::KEY_L:
			ShipRotTrans = Matrix(ROT_Y, -ShipRotAng) * ShipRotTrans;
			break;
		case AZUL_KEY::KEY_X:
			//Set Alignment is currently bugged.
			pSpriteString->SetAlignment(SpriteString::Right);
			pSpriteString->ChangeString(message);
			//SceneManager::SetNextScene(new SceneDemo);
			break;
		case AZUL_KEY::KEY_B:
			Matrix rotTrans = Matrix(TRANS, bulletOffset) * ShipRotTrans;
			pBulletPool->GetBullet()->Initialize(rotTrans, pBulletPool);
			
			pSpriteString->ChangeString(message);

			//Set Alignment is currently bugged.
			pSpriteString->SetAlignment(SpriteString::Left);
			message = "Bullets Fired: " + std::to_string(++bulletsFired);
			//pSpriteString->ChangeString(message);
			break;
		}
	}
}

void Frigate::KeyDown(AZUL_KEY k)
{
	if (!ignoreKeyPress) {
		switch (k) {
		case AZUL_KEY::KEY_J:
			ShipRotTrans = Matrix(ROT_Y, ShipRotAng) * ShipRotTrans;
			break;
		case AZUL_KEY::KEY_I:
			ShipRotTrans = Matrix(TRANS, Vect(0, 0, ShipTransSpeed)) * ShipRotTrans;
			break;
		case AZUL_KEY::KEY_K:
			ShipRotTrans = Matrix(TRANS, Vect(0, 0, -ShipTransSpeed)) * ShipRotTrans;
			break;
		case AZUL_KEY::KEY_L:
			ShipRotTrans = Matrix(ROT_Y, -ShipRotAng) * ShipRotTrans;
			break;
		}
	}
	
}

void Frigate::IgnoreKeyPress()
{
	ignoreKeyPress = true;
	ShipScale.set(SCALE, 1.0f, 1.0f, 1.0f);
}

void Frigate::Collision(Frigate*)
{
	this->collisionTrue = true;
}

void Frigate::Collision(Enemy*)
{
	this->collisionTrue = true;
}