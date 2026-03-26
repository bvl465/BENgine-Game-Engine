#include "TerrainManagerStrategyNull.h"
#include "TerrainManagerAttorney.h"

void TerrainManagerStrategyNull::Render()
{
	// No rendering for null strategy
}

TerrainObject* TerrainManagerStrategyNull::GetTerrainObject() const
{
	return nullptr;
}

void TerrainManagerStrategyNull::SetTerrainObject(TerrainObject* terrain)
{
	TerrainManagerAttorney::TerrainStrategyNull::SetTerrain(terrain);
}
