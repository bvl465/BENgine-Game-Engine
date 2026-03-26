//Ben La Monica
#pragma once
#ifndef _CameraManager
#define _CameraManager
class Camera;
class CameraManager
{
public:
	CameraManager();
	CameraManager(const CameraManager&) = delete;
	CameraManager& operator=(const CameraManager&) = delete;
	~CameraManager();


	//Sets the current 3D Camera to the Camera passed in.
	//Parameters:
	//cam - the Camera to set as the current 3D Camera.
	void SetCurrentCamera(Camera* cam);

	//Sets the current 2D camera to the camera passed in.
	//Parameters:
	//cam - the camera to set as the current 2D camera.
	void SetCurrentCamera2D(Camera* cam);

	//Returns a pointer to the current camera.
	Camera* GetCurrentCamera() const;

	//Returns a pointer to the current 2D camera.
	Camera* GetCurrentCamera2D() const;
	

private:
	//The current camera being used for 3D rendering.
	Camera* curCamera;

	//The current camera being used for 2D rendering.
	Camera* curCamera2D;

	//The default camera used for 3D rendering before one is set by the user.
	Camera* defaultCamera;

	//The default camera used for 2D rendering before one is set by the user.
	Camera* defaultCamera2D;
};
#endif _CameraManager