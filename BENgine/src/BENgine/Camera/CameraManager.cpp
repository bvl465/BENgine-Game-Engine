#include "CameraManager.h"
#include "Camera.h"
#include "../BENgine.h"

CameraManager::CameraManager()
{
	defaultCamera = new Camera(Camera::Type::PERSPECTIVE_3D);
	defaultCamera->setViewport(0, 0, BENgine::GetWidth(), BENgine::GetHeight());
	defaultCamera->setPerspective(35.0f, float(BENgine::GetWidth()) / float(BENgine::GetHeight()), 1.0f, 5000.0f);

	// Orient Camera
	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(50.0f, 50.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);
	defaultCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	defaultCamera->updateCamera();
	curCamera = defaultCamera;

	defaultCamera2D = new Camera(Camera::Type::ORTHOGRAPHIC_2D);

	defaultCamera2D->setViewport(0, 0, BENgine::GetWidth(), BENgine::GetHeight());
	defaultCamera2D->setOrthographic(-0.5f * float(BENgine::GetWidth()), 0.5f * float(BENgine::GetWidth()), -0.5f * float(BENgine::GetHeight()), 0.5f * float(BENgine::GetHeight()), 1.0f, 5000.0f);

	// Orient Camera
	Vect up2DCam(0.0f, 1.0f, 0.0f);
	Vect pos2DCam(0.0f, 0.0f, 0.0f);
	Vect lookAt2DCam(0.0f, 0.0f, -1.0f);
	defaultCamera2D->setOrientAndPosition(up2DCam, lookAt2DCam, pos2DCam);

	defaultCamera2D->updateCamera();
	curCamera2D = defaultCamera2D;
}

CameraManager::~CameraManager()
{
	delete defaultCamera;
	delete defaultCamera2D;
}

void CameraManager::SetCurrentCamera(Camera* cam)
{
	//implent using registration later incase the camera is switched during draw or just use a strategy pattern
	// and have one represent that the camera is in the draw stage and one that it is not in the draw stage and if
	// it is in the draw stage just crash and leave an error giving the naughty user the finger wag of shame.
	// I could have the scene manager switch it to the other strategy (through the attorney of course)
	//------------------------------------------------------
	//     /\   /\
	//    |  | |  |      Wake up, Ben...
	//     \ --- /       The Matrix has you...
	//    / | _ | \      Don't follow the white rabbit...
	//    \(= X =)/      Knock, knock, Ben.
	//     '~~~~~'
	//     / L_ \`\
	//   (\`~._)(_/
	//    (..)_; )_
	//    '--' `---'
	//------------------------------------------------------
	curCamera = cam;
}

void CameraManager::SetCurrentCamera2D(Camera* cam)
{
	curCamera2D = cam;
}

Camera* CameraManager::GetCurrentCamera() const
{
	return curCamera;
}

Camera* CameraManager::GetCurrentCamera2D() const
{
	return curCamera2D;
}

