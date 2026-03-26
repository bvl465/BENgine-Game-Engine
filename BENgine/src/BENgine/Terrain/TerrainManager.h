//Ben La Monica
#pragma once
#ifndef _TerrainManager
#define _TerrainManager
#include <string>
class TerrainObject;
class TerrainManagerStrategyBase;
class TerrainManagerStrategyNull;
class TerrainManagerStrategyInitialized;
class TerrainManager
{
public:
	TerrainManager();
	TerrainManager(const TerrainManager&) = delete;
	TerrainManager& operator=(const TerrainManager&) = delete;
	~TerrainManager();

	//Renders the current terrain if there is one. If there isn't a current terrain it does nothing.
	void Render();

	//Sets the current terrain to the terrain with the matching key in the TerrainObjectManager.
	//Parameters:
	//terrainKey: The key of the terrain to set as the current terrain. Must match a key in the TerrainObjectManager.
	void SetCurrentTerrain(std::string terrainKey);

	//Returns a pointer to the current TerrainObject.
	TerrainObject* GetCurrentTerrain() const;


private:
	friend class TerrainManagerAttorney; //Allow attorney to set the current terrain


	void privSetCurrentTerrain(TerrainObject* terrain);
	void privRender();
	TerrainObject* privGetCurrentTerrain() const;
	TerrainObject* curTerrain;

	TerrainManagerStrategyBase* strategy;
	TerrainManagerStrategyNull* nullStrategy;
	TerrainManagerStrategyInitialized* initializedStrategy;

};
#endif _TerrainManager