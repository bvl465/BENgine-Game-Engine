//Ben La Monica
#include "SceneSwitchingDemo.h"
#include "FlightScene.h"
#include "SceneDemo.h"
#include "../src/BENgine/Scene/SceneManager.h"
#include "../src/BENgine/Scene/Scene.h"
SceneSwitchingDemo::SceneSwitchingDemo()
{
	SubmitKeyRegistration(AZUL_KEY::KEY_T, KeyEvent::KEY_PRESSED);
	SubmitKeyRegistration(AZUL_KEY::KEY_Y, KeyEvent::KEY_PRESSED);

}

SceneSwitchingDemo::~SceneSwitchingDemo()
{
	SubmitKeyDeregistration(AZUL_KEY::KEY_T, KeyEvent::KEY_PRESSED);
	SubmitKeyDeregistration(AZUL_KEY::KEY_Y, KeyEvent::KEY_PRESSED);

}


void SceneSwitchingDemo::KeyPress(AZUL_KEY k)
{
	switch (k) {
	case AZUL_KEY::KEY_T:
		if (sceneSwitchInProgress == false) {
			SceneManager::SetNextScene(new FlightScene);
			sceneSwitchInProgress = true;
		}
		
		break;
	case AZUL_KEY::KEY_Y:
		if (sceneSwitchInProgress == false) {
			SceneManager::SetNextScene(new SceneDemo);
			sceneSwitchInProgress = true;
		}
		
		break;
	}
}