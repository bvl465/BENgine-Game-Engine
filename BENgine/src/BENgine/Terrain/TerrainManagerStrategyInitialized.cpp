#include "TerrainManagerStrategyInitialized.h"
#include "TerrainManagerAttorney.h"
void TerrainManagerStrategyInitialized::Render()
{
	TerrainManagerAttorney::TerrainStrategyInitialized::Render();
}

TerrainObject* TerrainManagerStrategyInitialized::GetTerrainObject() const
{
	return TerrainManagerAttorney::TerrainStrategyInitialized::GetTerrain();
}

void TerrainManagerStrategyInitialized::SetTerrainObject(TerrainObject* terrain)
{
	terrain;
	//do nothing its already been initialized
}
