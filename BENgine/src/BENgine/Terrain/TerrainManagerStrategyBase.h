//Ben La Monica
#pragma once
#ifndef _TerrainManagerStrategyBase
#define _TerrainManagerStrategyBase
class TerrainObject;
class TerrainManagerStrategyBase
{
public:

	TerrainManagerStrategyBase() = default;
	TerrainManagerStrategyBase(const TerrainManagerStrategyBase&) = delete;
	TerrainManagerStrategyBase& operator=(const TerrainManagerStrategyBase&) = default;
	~TerrainManagerStrategyBase() = default;



	virtual void Render() = 0;


	virtual TerrainObject* GetTerrainObject() const = 0;

	virtual void SetTerrainObject(TerrainObject* terrain) = 0;


private:

	//Nothing for now

};
#endif _TerrainManagerStrategyBase