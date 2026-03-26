//Ben La Monica
#pragma once
#ifndef _TerrainManagerStrategyInitialized
#define _TerrainManagerStrategyInitialized
#include "TerrainManagerStrategyBase.h"
class TerrainObject;
class TerrainManagerStrategyInitialized : public TerrainManagerStrategyBase
{
public:

	TerrainManagerStrategyInitialized() = default;
	TerrainManagerStrategyInitialized(const TerrainManagerStrategyInitialized&) = default;
	TerrainManagerStrategyInitialized& operator=(const TerrainManagerStrategyInitialized&) = default;
	~TerrainManagerStrategyInitialized() = default;

	virtual void Render() override;

	virtual TerrainObject* GetTerrainObject() const override;

	virtual void SetTerrainObject(TerrainObject* terrain) override;


private:
	

	//Nothing for now

};
#endif _TerrainManagerStrategyInitialized