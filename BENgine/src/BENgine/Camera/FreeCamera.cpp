#include "FreeCamera.h"
#include "../BENgine.h"
FreeCamera::FreeCamera() : freeCam(new Camera(Camera::Type::PERSPECTIVE_3D))
{

	freeCam->setViewport(0, 0, BENgine::GetWidth(), BENgine::GetHeight());
	freeCam->setPerspective(35.0f, float(BENgine::GetWidth()) / float(BENgine::GetHeight()), 1.0f, 5000.0f);
	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(50.0f, 50.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);
	freeCam->setOrientAndPosition(camUp * camRot, camPos + camDir * camRot, camPos);
	//freeCam->setOrientAndPosition(camUp, camDir, camPos);
	freeCam->updateCamera();
	SceneEntry();
}

FreeCamera::~FreeCamera()
{
	SceneExit();
	delete freeCam; //delete the camera
}

void FreeCamera::SceneEntry()
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

void FreeCamera::SceneExit()
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

void FreeCamera::KeyPress(AZUL_KEY k)
{
	switch (k) {
	case AZUL_KEY::KEY_W:
		camPos += Vect(0.f, 0.f, 1.f) * camRot * camTranSpeed;
		break;
	case AZUL_KEY::KEY_S:
		camPos += Vect(0.f, 0.f, 1.f) * camRot * -camTranSpeed;
		break;
	case AZUL_KEY::KEY_D:
		camPos += Vect(1.f, 0.f, 0.f) * camRot * -camTranSpeed;
		break;
	case AZUL_KEY::KEY_A:
		camPos += Vect(1.f, 0.f, 0.f) * camRot * camTranSpeed;
		break;
	case AZUL_KEY::KEY_Q:
		camTranSpeed = camTranSpeedSlow;
		camRotSpeed = camRotSpeedSlow;
		break;
	case AZUL_KEY::KEY_E:
		camTranSpeed = camTranSpeedNormal;
		camRotSpeed = camRotSpeedNormal;
		break;
	case AZUL_KEY::KEY_LEFT_SHIFT:
		camPos += Vect(0.f, 1.f, 0.f) * camRot * camTranSpeed;
		break;
	case AZUL_KEY::KEY_LEFT_CONTROL:
		camPos += Vect(0.f, -1.f, 0.f) * camRot * camTranSpeed;
		break;
	case AZUL_KEY::KEY_ARROW_LEFT:
		camRot *= Matrix(ROT_Y, camRotSpeed);
		break;
	case AZUL_KEY::KEY_ARROW_RIGHT:
		camRot *= Matrix(ROT_Y, -camRotSpeed);
		break;
	case AZUL_KEY::KEY_ARROW_DOWN:
		camRot *= Matrix(ROT_AXIS_ANGLE, Vect(1.f, 0.f, 0.f) * camRot, camRotSpeed);
		break;
	case AZUL_KEY::KEY_ARROW_UP:
		camRot *= Matrix(ROT_AXIS_ANGLE, Vect(1.f, 0.f, 0.f) * camRot, -camRotSpeed);
		break;
	}
	freeCam->setOrientAndPosition(camUp * camRot, camPos + camDir * camRot, camPos);
	freeCam->updateCamera();
}

void FreeCamera::KeyDown(AZUL_KEY k)
{
	
	switch (k) {
	case AZUL_KEY::KEY_W:
		camPos += Vect(0.f, 0.f, 1.f) * camRot * camTranSpeed;
		break;
	case AZUL_KEY::KEY_S:
		camPos += Vect(0.f, 0.f, 1.f) * camRot * -camTranSpeed;
		break;
	case AZUL_KEY::KEY_D:
		camPos += Vect(1.f, 0.f, 0.f) * camRot * -camTranSpeed;
		break;
	case AZUL_KEY::KEY_A:
		camPos += Vect(1.f, 0.f, 0.f) * camRot * camTranSpeed;
		break;
	case AZUL_KEY::KEY_LEFT_SHIFT:
		camPos += Vect(0.f, 1.f, 0.f) * camRot * camTranSpeed;
		break;
	case AZUL_KEY::KEY_LEFT_CONTROL:
		camPos += Vect(0.f, -1.f, 0.f) * camRot * camTranSpeed;
		break;
	case AZUL_KEY::KEY_ARROW_LEFT:
		camRot *= Matrix(ROT_Y, camRotSpeed);
		break;
	case AZUL_KEY::KEY_ARROW_RIGHT:
		camRot *= Matrix(ROT_Y, -camRotSpeed);
		break;
	case AZUL_KEY::KEY_ARROW_DOWN:
		camRot *= Matrix(ROT_AXIS_ANGLE, Vect(1.f, 0.f, 0.f) * camRot, camRotSpeed);
		break;
	case AZUL_KEY::KEY_ARROW_UP:
		camRot *= Matrix(ROT_AXIS_ANGLE, Vect(1.f, 0.f, 0.f) * camRot, -camRotSpeed);
		break;
	}
	freeCam->setOrientAndPosition(camUp * camRot, camPos + camDir * camRot, camPos);
	freeCam->updateCamera();
}

void FreeCamera::SetCameraPos(const Vect& inPos)
{
	camPos = inPos;
}

Camera* FreeCamera::GetCamera() const
{
	return freeCam;
}
