#include "TerrainManager.h"
#include "TerrainManagerStrategyBase.h"
#include "TerrainManagerStrategyNull.h"
#include "TerrainManagerStrategyInitialized.h"
#include "TerrainObject.h"
#include "../Asset Managers/Terrain Object Manager/TerrainObjectManager.h"
#include "../Scene/SceneManager.h"
#include "../Camera/CameraManager.h"
#include "../Scene/Scene.h"

TerrainManager::TerrainManager() : curTerrain(nullptr)
{
	nullStrategy = new TerrainManagerStrategyNull();
	initializedStrategy = new TerrainManagerStrategyInitialized();

	// Initially set the strategy to null strategy
	strategy = nullStrategy;

	// Set the current terrain to null
	curTerrain = nullptr;
}

TerrainManager::~TerrainManager()
{
	delete nullStrategy;
	delete initializedStrategy;
}

void TerrainManager::Render()
{
	strategy->Render();
}

void TerrainManager::SetCurrentTerrain(std::string terrainKey)
{
	TerrainObject* terrain = TerrainObjectManager::GetTerrainObject(terrainKey);
	assert(terrain != nullptr && "TerrainManager::SetCurrentTerrain: terrain cannot be initialized to nullptr");

	strategy->SetTerrainObject(TerrainObjectManager::GetTerrainObject(terrainKey));

}

TerrainObject* TerrainManager::GetCurrentTerrain() const
{
	return curTerrain;
    //return strategy->GetTerrainObject();
}

void TerrainManager::privSetCurrentTerrain(TerrainObject* terrain)
{
	curTerrain = terrain;
	strategy = initializedStrategy;
}

void TerrainManager::privRender()
{
	curTerrain->Render((SceneManager::GetCurrentScene())->GetCurrentCamera());
}

TerrainObject* TerrainManager::privGetCurrentTerrain() const
{
	return curTerrain;
}
