#ifndef _FirstPersonFlightCam
#define _FirstPersonFlightCam

#include "AzulCore.h"
#include "../src/BENgine/Game Object/GameObject.h"
class TerrainObject;
class FirstPersonFlightCam : public GameObject
{
public:
    FirstPersonFlightCam();
    FirstPersonFlightCam(const FirstPersonFlightCam&) = delete;
    FirstPersonFlightCam& operator=(const FirstPersonFlightCam&) = delete;
    ~FirstPersonFlightCam();


    //maybe make these private because I don't want the user calling scene entry and exit
    void SceneEntry() override;
    void SceneExit() override;
    void KeyPress(AZUL_KEY k) override;
    void KeyDown(AZUL_KEY k) override;
    void SetCameraPos(const Vect& inPos);

    Camera* GetCamera() const;

	void Update() override;

    void LookLeft();
	void LookRight();
	void LookUp();
	void LookDown();
	void MoveForward();
	void MoveBackward();
	void BankLeft();
	void BankRight();
	void PitchUp();
	void PitchDown();

private:

    Matrix camRot = Matrix(IDENTITY);		// No rotation initially
    Vect camUp = Vect(0.f, 1.f, 0.f);			// Using local Y axis as 'Up'
    Vect camDir = Vect(0.f, 0.f, 1.f);			// Using the local Z axis as 'forward'
    Vect camPos = Vect(50.f, 50.f, 100.0f);
    float camTranSpeed = 1.f;
    float camTranSpeedNormal = .5f;
    float camTranSpeedSlow = .5f;
    float camRotSpeed = .02f;
    float camRotSpeedNormal = .02f;
    float camRotSpeedSlow = .01f;
	const float horCockpitViewBoundsMin = -.4f;
	const float horCockpitViewBoundsMax = .4f;
	const float vertCockpitViewBoundsMin = -.1f;
	const float vertCockpitViewBoundsMax = .1f;
	float horCockpitViewOffset = 0.f; // Horizontal offset for the cockpit view
	float vertCockpitViewOffset = 0.f; // Vertical offset for the cockpit view
	const float horCockpitViewSpeed = .03f; // Speed of horizontal cockpit view movement
	const float vertCockpitViewSpeed = .009f; // Speed of vertical cockpit view movement
	TerrainObject* terrain = nullptr; // Pointer to the terrain object for height calculations
    Camera* flightCam; //the camera that is being controlled
};

#endif _FirstPersonFlightCam