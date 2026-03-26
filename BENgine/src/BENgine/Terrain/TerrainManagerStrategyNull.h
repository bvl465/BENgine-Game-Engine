//Ben La Monica
#pragma once
#ifndef _TerrainNullStrategy
#define _TerrainNullStrategy
#include "TerrainManagerStrategyBase.h"
class TerrainManagerStrategyNull : public TerrainManagerStrategyBase
{
public:
	TerrainManagerStrategyNull() = default;
	TerrainManagerStrategyNull(const TerrainManagerStrategyNull&) = delete;
	TerrainManagerStrategyNull& operator=(const TerrainManagerStrategyNull&) = delete;
	~TerrainManagerStrategyNull() = default;

	virtual void Render() override;

	virtual TerrainObject* GetTerrainObject() const override;

	virtual void SetTerrainObject(TerrainObject* terrain) override;

private:

};
#endif _TerrainNullStrategy