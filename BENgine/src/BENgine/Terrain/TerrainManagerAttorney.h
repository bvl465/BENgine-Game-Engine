//Ben La Monica
#pragma once
#ifndef _TerrainManagerAttorney
#define _TerrainManagerAttorney
#include "AzulCore.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"
#include "TerrainManager.h"
class TerrainManagerAttorney
{
public:
	class TerrainStrategyNull
	{
		friend class TerrainManagerStrategyNull;

	private:
		static void SetTerrain(TerrainObject* terrainObject) { SceneManager::GetCurrentScene()->GetTerrainManager()->TerrainManager::privSetCurrentTerrain(terrainObject); }
	};

	class TerrainStrategyInitialized
	{
		friend class TerrainManagerStrategyInitialized;

	private:
		static TerrainObject* GetTerrain() { return SceneManager::GetCurrentScene()->GetTerrainManager()->GetCurrentTerrain(); }
		static void Render() { SceneManager::GetCurrentScene()->GetTerrainManager()->TerrainManager::privRender(); }
	};
};
#endif _TerrainManagerAttorney