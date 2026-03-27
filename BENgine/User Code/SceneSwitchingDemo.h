#pragma once
#ifndef _SceneSwitchingDemo
#define _SceneSwitchingDemo
#include "../src/BENgine/Game Object/GameObject.h"

#include "../src/BENgine/BENgine.h"
class Layer;
class SceneSwitchingDemo : public GameObject
{
public:
	SceneSwitchingDemo();
	SceneSwitchingDemo(const SceneSwitchingDemo&) = delete;
	SceneSwitchingDemo& operator=(const SceneSwitchingDemo&) = delete;
	~SceneSwitchingDemo();
	virtual void KeyPress(AZUL_KEY k) override;

private:
	bool sceneSwitchInProgress = false;
};
#endif _SceneSwitchingDemo