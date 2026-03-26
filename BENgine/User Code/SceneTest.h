//Ben La Monica
#pragma once
#ifndef _SceneTest
#define _SceneTest
#include "../src/BENgine/Scene/Scene.h"
class WorldPlane;
class Axis;
class Frigate;
class SceneTest : public Scene
{
public:
	SceneTest() = default;
	SceneTest(const SceneTest&) = delete;
	SceneTest& operator=(const SceneTest&) = delete;
	~SceneTest();


	//virtual void Draw() override;
	//virtual void Update() override;

private:
	Frigate* frigate = nullptr;
	virtual void Initialize() override;
	virtual void SceneEnd() override;

};
#endif _SceneTest