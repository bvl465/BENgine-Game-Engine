#include "FirstPersonFlightCam.h"
#include "../src/BENgine/BENgine.h"
#include "../src/BENgine/Math Tools/BENgineMathTools.h"
#include "../src/BENgine/Scene/SceneManager.h"
#include "../src/BENgine/Scene/Scene.h"
#include "../src/BENgine/Terrain/TerrainManager.h"
#include "../src/BENgine/Terrain/TerrainObject.h"



FirstPersonFlightCam::FirstPersonFlightCam() : flightCam(new Camera(Camera::Type::PERSPECTIVE_3D))
{
	terrain = SceneManager::GetCurrentScene()->GetTerrainManager()->GetCurrentTerrain();
	flightCam->setViewport(0, 0, BENgine::GetWidth(), BENgine::GetHeight());
	flightCam->setPerspective(35.0f, float(BENgine::GetWidth()) / float(BENgine::GetHeight()), 1.0f, 5000.0f);
	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(50.0f, 50.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);
	flightCam->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	flightCam->updateCamera();
	SceneEntry();
}

FirstPersonFlightCam::~FirstPersonFlightCam()
{
	SceneExit();
	delete flightCam; //delete the camera
}

void FirstPersonFlightCam::SceneEntry()
{
	SubmitKeyRegistration(AZUL_KEY::KEY_W, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_A, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_S, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_D, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_LEFT_SHIFT, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_LEFT_CONTROL, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_Q, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_E, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_W, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_A, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_S, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_D, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_LEFT_SHIFT, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_LEFT_CONTROL, KeyEvent::KEY_DOWN);


	SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_UP, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_DOWN, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_LEFT, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_RIGHT, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_UP, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_DOWN, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_LEFT, KeyEvent::KEY_DOWN);
	SubmitKeyRegistration(AZUL_KEY::KEY_ARROW_RIGHT, KeyEvent::KEY_DOWN);

	//register for input
}

void FirstPersonFlightCam::SceneExit()
{
	SubmitKeyDeregistration(AZUL_KEY::KEY_W, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_A, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_S, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_D, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_LEFT_SHIFT, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_LEFT_CONTROL, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_Q, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_E, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_W, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_A, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_S, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_D, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_LEFT_SHIFT, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_LEFT_CONTROL, KeyEvent::KEY_DOWN);


	SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_UP, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_DOWN, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_LEFT, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_RIGHT, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_UP, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_DOWN, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_LEFT, KeyEvent::KEY_DOWN);
	SubmitKeyDeregistration(AZUL_KEY::KEY_ARROW_RIGHT, KeyEvent::KEY_DOWN);
}

void FirstPersonFlightCam::KeyPress(AZUL_KEY k)
{

	switch (k) {
	case AZUL_KEY::KEY_W:
		camPos += Vect(0.f, 0.f, 1.f) * camRot * camTranSpeed;
		break;
	case AZUL_KEY::KEY_S:
		camPos += Vect(0.f, 0.f, 1.f) * camRot * -camTranSpeed;
		break;
	case AZUL_KEY::KEY_D:
		camRot *= Matrix(ROT_AXIS_ANGLE, Vect(0.f, 0.f, 1.f) * camRot, camRotSpeed);
		break;
	case AZUL_KEY::KEY_A:
		camRot *= Matrix(ROT_AXIS_ANGLE, Vect(0.f, 0.f, 1.f) * camRot, -camRotSpeed);
		break;
	case AZUL_KEY::KEY_ARROW_LEFT:
		horCockpitViewOffset = BENgineMathTools::FloatClamp(horCockpitViewOffset + horCockpitViewSpeed, horCockpitViewBoundsMin, horCockpitViewBoundsMax);
		//camRot *= Matrix(ROT_Y, camRotSpeed);
		break;
	case AZUL_KEY::KEY_ARROW_RIGHT:
		horCockpitViewOffset = BENgineMathTools::FloatClamp(horCockpitViewOffset - horCockpitViewSpeed, horCockpitViewBoundsMin, horCockpitViewBoundsMax);
		//camRot *= Matrix(ROT_Y, -camRotSpeed);
		break;
	case AZUL_KEY::KEY_ARROW_DOWN:
		vertCockpitViewOffset = BENgineMathTools::FloatClamp(vertCockpitViewOffset - vertCockpitViewSpeed, vertCockpitViewBoundsMin, vertCockpitViewBoundsMax);
		break;
	case AZUL_KEY::KEY_ARROW_UP:
		vertCockpitViewOffset = BENgineMathTools::FloatClamp(vertCockpitViewOffset + vertCockpitViewSpeed, vertCockpitViewBoundsMin, vertCockpitViewBoundsMax);
		break;
	case AZUL_KEY::KEY_LEFT_CONTROL:
		camRot *= Matrix(ROT_AXIS_ANGLE, Vect(1.f, 0.f, 0.f) * camRot, -camRotSpeed);
		break;
	case AZUL_KEY::KEY_LEFT_SHIFT:
		camRot *= Matrix(ROT_AXIS_ANGLE, Vect(1.f, 0.f, 0.f) * camRot, camRotSpeed);
		break;
	}
	Vect camTerrainPos = Vect(camPos.X(), BENgineMathTools::FloatClamp(camPos.Y(), (terrain->GetTerrainObjectHeight(camPos)) + 10.f, camPos.Y() + 11.f), camPos.Z());
	camPos = camTerrainPos;
	//flightCam->setOrientAndPosition(camUp * camRot, camTerrainPos + camDir  * camRot, camTerrainPos);
	//flightCam->setOrientAndPosition(camUp * camRot, camPos + camDir * camRot, camPos);
	//flightCam->setOrientAndPosition(camUp * camRot, camTerrainPos + camDir * camRot + Vect(horCockpitViewOffset, 0, 0) * camRot, camTerrainPos);
	//flightCam->setOrientAndPosition(camUp * camRot, camTerrainPos + camDir * camRot + (Vect(horCockpitViewOffset, 0, 0) * camRot), camTerrainPos);
	//flightCam->setOrientAndPosition(camUp * camRot, camTerrainPos + (camDir + (Vect(horCockpitViewOffset, 0, 0)) * camRot), camTerrainPos);
	//flightCam->setOrientAndPosition(camUp * camRot, camTerrainPos + (camDir) * camRot, camTerrainPos);
	//flightCam->setOrientAndPosition(camUp * camRot, camTerrainPos + (camDir + Vect(horCockpitViewOffset, 0, vertCockpitViewOffset)) * camRot, camTerrainPos);
	flightCam->setOrientAndPosition(camUp * camRot, camTerrainPos + (camDir + Vect(horCockpitViewOffset, vertCockpitViewOffset, 0)) * camRot, camTerrainPos);
	flightCam->updateCamera();
}

void FirstPersonFlightCam::KeyDown(AZUL_KEY k)
{

	//switch (k) {
	//case AZUL_KEY::KEY_LEFT_SHIFT:
	//	camPos += Vect(0.f, 0.f, 1.f) * camRot * camTranSpeed;
	//	break;
	//case AZUL_KEY::KEY_LEFT_CONTROL:
	//	camPos += Vect(0.f, 0.f, 1.f) * camRot * -camTranSpeed;
	//	break;
	//case AZUL_KEY::KEY_D:
	//	camRot *= Matrix(ROT_AXIS_ANGLE, Vect(0.f, 0.f, 1.f) * camRot, camRotSpeed);
	//	break;
	//case AZUL_KEY::KEY_A:
	//	camRot *= Matrix(ROT_AXIS_ANGLE, Vect(0.f, 0.f, 1.f) * camRot, -camRotSpeed);
	//	break;
	//case AZUL_KEY::KEY_ARROW_LEFT:
	//	horCockpitViewOffset = BENgineMathTools::FloatClamp(horCockpitViewOffset - horCockpitViewSpeed, horCockpitViewBoundsMin, horCockpitViewBoundsMax);
	//	//camRot *= Matrix(ROT_Y, camRotSpeed);
	//	break;
	//case AZUL_KEY::KEY_ARROW_RIGHT:
	//	horCockpitViewOffset = BENgineMathTools::FloatClamp(horCockpitViewOffset + horCockpitViewSpeed, horCockpitViewBoundsMin, horCockpitViewBoundsMax);
	//	//camRot *= Matrix(ROT_Y, -camRotSpeed);
	//	break;
	//case AZUL_KEY::KEY_ARROW_DOWN:
	//	camRot *= Matrix(ROT_AXIS_ANGLE, Vect(1.f, 0.f, 0.f) * camRot, -camRotSpeed);
	//	break;
	//case AZUL_KEY::KEY_ARROW_UP:
	//	camRot *= Matrix(ROT_AXIS_ANGLE, Vect(1.f, 0.f, 0.f) * camRot, camRotSpeed);
	//	break;
	//}
	//Vect camTerrainPos = Vect(camPos.X(), BENgineMathTools::FloatClamp(camPos.Y(), (terrain->GetTerrainObjectHeight(camPos)) + 10.f, camPos.Y() + 10.f), camPos.Z());
	////flightCam->setOrientAndPosition(camUp * camRot, camTerrainPos + camDir * camRot, camTerrainPos);
	////flightCam->setOrientAndPosition(camUp * camRot, camTerrainPos + (camDir + (Vect(horCockpitViewOffset, 0, 0)) * camRot), camTerrainPos);
	//flightCam->setOrientAndPosition(camUp * camRot, camTerrainPos + (camDir + Vect(horCockpitViewOffset, 0, 0)) * camRot, camTerrainPos);
	//flightCam->updateCamera();

	switch (k) {
	case AZUL_KEY::KEY_W:
		camPos += Vect(0.f, 0.f, 1.f) * camRot * camTranSpeed;
		break;
	case AZUL_KEY::KEY_S:
		camPos += Vect(0.f, 0.f, 1.f) * camRot * -camTranSpeed;
		break;
	case AZUL_KEY::KEY_D:
		camRot *= Matrix(ROT_AXIS_ANGLE, Vect(0.f, 0.f, 1.f) * camRot, camRotSpeed);
		break;
	case AZUL_KEY::KEY_A:
		camRot *= Matrix(ROT_AXIS_ANGLE, Vect(0.f, 0.f, 1.f) * camRot, -camRotSpeed);
		break;
	case AZUL_KEY::KEY_ARROW_LEFT:
		horCockpitViewOffset = BENgineMathTools::FloatClamp(horCockpitViewOffset + horCockpitViewSpeed, horCockpitViewBoundsMin, horCockpitViewBoundsMax);
		//camRot *= Matrix(ROT_Y, camRotSpeed);
		break;
	case AZUL_KEY::KEY_ARROW_RIGHT:
		horCockpitViewOffset = BENgineMathTools::FloatClamp(horCockpitViewOffset - horCockpitViewSpeed, horCockpitViewBoundsMin, horCockpitViewBoundsMax);
		//camRot *= Matrix(ROT_Y, -camRotSpeed);
		break;
	case AZUL_KEY::KEY_ARROW_DOWN:
		vertCockpitViewOffset = BENgineMathTools::FloatClamp(vertCockpitViewOffset - vertCockpitViewSpeed, vertCockpitViewBoundsMin, vertCockpitViewBoundsMax);
		break;
	case AZUL_KEY::KEY_ARROW_UP:
		vertCockpitViewOffset = BENgineMathTools::FloatClamp(vertCockpitViewOffset + vertCockpitViewSpeed, vertCockpitViewBoundsMin, vertCockpitViewBoundsMax);
		break;
	case AZUL_KEY::KEY_LEFT_CONTROL:
		camRot *= Matrix(ROT_AXIS_ANGLE, Vect(1.f, 0.f, 0.f) * camRot, -camRotSpeed);
		break;
	case AZUL_KEY::KEY_LEFT_SHIFT:
		camRot *= Matrix(ROT_AXIS_ANGLE, Vect(1.f, 0.f, 0.f) * camRot, camRotSpeed);
		break;
	}
	Vect camTerrainPos = Vect(camPos.X(), BENgineMathTools::FloatClamp(camPos.Y(), (terrain->GetTerrainObjectHeight(camPos)) + 10.f, camPos.Y() + 11.f), camPos.Z());
	camPos = camTerrainPos;
	//flightCam->setOrientAndPosition(camUp * camRot, camTerrainPos + camDir  * camRot, camTerrainPos);
	//flightCam->setOrientAndPosition(camUp * camRot, camPos + camDir * camRot, camPos);
	//flightCam->setOrientAndPosition(camUp * camRot, camTerrainPos + camDir * camRot + Vect(horCockpitViewOffset, 0, 0) * camRot, camTerrainPos);
	//flightCam->setOrientAndPosition(camUp * camRot, camTerrainPos + camDir * camRot + (Vect(horCockpitViewOffset, 0, 0) * camRot), camTerrainPos);
	//flightCam->setOrientAndPosition(camUp * camRot, camTerrainPos + (camDir + (Vect(horCockpitViewOffset, 0, 0)) * camRot), camTerrainPos);
	//flightCam->setOrientAndPosition(camUp * camRot, camTerrainPos + (camDir) * camRot, camTerrainPos);
	flightCam->setOrientAndPosition(camUp * camRot, camTerrainPos + (camDir + Vect(horCockpitViewOffset, vertCockpitViewOffset, 0)) * camRot, camTerrainPos);
	flightCam->updateCamera();
}

void FirstPersonFlightCam::SetCameraPos(const Vect& inPos)
{
	camPos = inPos;
}

Camera* FirstPersonFlightCam::GetCamera() const
{
	return flightCam;
}

void FirstPersonFlightCam::Update()
{
	Vect camTerrainPos = Vect(camPos.X(), BENgineMathTools::FloatClamp(camPos.Y(), (terrain->GetTerrainObjectHeight(camPos)) + 10.f, camPos.Y() + 11.f), camPos.Z());
	camPos = camTerrainPos;
	flightCam->setOrientAndPosition(camUp * camRot, camTerrainPos + (camDir + Vect(horCockpitViewOffset, vertCockpitViewOffset, 0)) * camRot, camTerrainPos);
	flightCam->updateCamera();
}

void FirstPersonFlightCam::PitchDown()
{
	camRot *= Matrix(ROT_AXIS_ANGLE, Vect(1.f, 0.f, 0.f) * camRot, -camRotSpeed);
}

void FirstPersonFlightCam::PitchUp()
{
	camRot *= Matrix(ROT_AXIS_ANGLE, Vect(1.f, 0.f, 0.f) * camRot, camRotSpeed);
}
void FirstPersonFlightCam::BankLeft()
{
	camRot *= Matrix(ROT_AXIS_ANGLE, Vect(0.f, 0.f, 1.f) * camRot, -camRotSpeed);
}
void FirstPersonFlightCam::BankRight()
{
	camRot *= Matrix(ROT_AXIS_ANGLE, Vect(0.f, 0.f, 1.f) * camRot, camRotSpeed);
}
void FirstPersonFlightCam::LookLeft()
{
	horCockpitViewOffset = BENgineMathTools::FloatClamp(horCockpitViewOffset - horCockpitViewSpeed, horCockpitViewBoundsMin, horCockpitViewBoundsMax);
}
void FirstPersonFlightCam::LookRight()
{
	horCockpitViewOffset = BENgineMathTools::FloatClamp(horCockpitViewOffset + horCockpitViewSpeed, horCockpitViewBoundsMin, horCockpitViewBoundsMax);
}
void FirstPersonFlightCam::LookUp()
{
	vertCockpitViewOffset = BENgineMathTools::FloatClamp(vertCockpitViewOffset + vertCockpitViewSpeed, vertCockpitViewBoundsMin, vertCockpitViewBoundsMax);
}
void FirstPersonFlightCam::LookDown()
{
	vertCockpitViewOffset = BENgineMathTools::FloatClamp(vertCockpitViewOffset - vertCockpitViewSpeed, vertCockpitViewBoundsMin, vertCockpitViewBoundsMax);
}

void FirstPersonFlightCam::MoveForward()
{
	camPos += Vect(0.f, 0.f, 1.f) * camRot * camTranSpeed;
}
void FirstPersonFlightCam::MoveBackward()
{
	camPos += Vect(0.f, 0.f, 1.f) * camRot * -camTranSpeed;
}