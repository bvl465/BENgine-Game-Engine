//Ben La Monica
#include "../BENgine/BENgine.h"


void BENgine::GameInitialize() {

	// Game Window Device setup
	this->setWindowName("BENgine Demo");
	this->SetClearColor(0.4f, 0.4f, 0.8f, 1.0f);

	RECT rc;
	GetWindowRect(GetDesktopWindow(), &rc);

	//this->SetWidthHeight((rc.right - rc.left) / 2, (rc.bottom - rc.top) / 2);  // 1/4 of the screen

	this->SetWidthHeight(1280, 720);  // set dimension directly
	//this->setWidthHeight(800, 600);  // set dimension directly

	// Use this area, for one time non-graphic creation
}