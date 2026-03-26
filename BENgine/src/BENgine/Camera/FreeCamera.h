#ifndef _FreeCamera
#define _FreeCamera

#include "AzulCore.h"
#include "../Game Object/GameObject.h"

class FreeCamera : public GameObject
{
public:
    FreeCamera();
    FreeCamera(const FreeCamera&) = delete;
    FreeCamera& operator=(const FreeCamera&) = delete;
    ~FreeCamera();


	//maybe make these private because I don't want the user calling scene entry and exit
    void SceneEntry() override;
	void SceneExit() override;
    void KeyPress(AZUL_KEY k) override;
    void KeyDown(AZUL_KEY k) override;
	void SetCameraPos(const Vect& inPos);
    
    Camera* GetCamera() const;



private:

    Matrix camRot = Matrix(IDENTITY);		// No rotation initially
    Vect camUp = Vect(0.f, 1.f, 0.f);			// Using local Y axis as 'Up'
    Vect camDir = Vect(0.f, 0.f, 1.f);			// Using the local Z axis as 'forward'
    Vect camPos = Vect(50.f, 50.f, 100.0f);
    float camTranSpeed = 2.f;
    float camTranSpeedNormal = 2.f;
    float camTranSpeedSlow = .5f;
    float camRotSpeed = .02f;
    float camRotSpeedNormal = .02f;
    float camRotSpeedSlow = .01f;
    Camera* freeCam; //the camera that is being controlled
};

#endif _FreeCamera