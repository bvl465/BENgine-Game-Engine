#include "SceneTest.h"
#include "Frigate.h"
#include "../src/BENgine/Scene/SceneManager.h"
SceneTest::~SceneTest()
{

}
void SceneTest::Initialize()
{
	(SceneManager::GetCurrentScene())->GetTerrainManager()->SetCurrentTerrain("pTerrainTestTerrainObject");
	frigate = new Frigate();
}

void SceneTest::SceneEnd()
{
	delete frigate;
	//delete plane;
	//delete frigate;
	//delete axis;
}
