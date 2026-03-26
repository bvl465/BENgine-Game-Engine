#pragma once
#ifndef _TerrainRectangularArea
#define _TerrainRectangularArea
#include "TerrainObject.h"
class Collidable;
class TRAIterator;
class TerrainRectangleArea
{
public:
	TerrainRectangleArea() = default;

	//If the terrain changes then initializing it with a terrain object could be dangerous since there is no registration for terrain

	TerrainRectangleArea(TerrainObject* terrain, CellCoordinates minimumCoord, CellCoordinates maximumCoord);
	TerrainRectangleArea(const TerrainRectangleArea&) = default;
	TerrainRectangleArea(Collidable* collidable, TerrainObject* terrain);
	


	CellCoordinates GetMin() const;
	CellCoordinates GetMax() const;
	TRAIterator begin();
	TRAIterator end();

private:
	friend class TerrainRectangleAreaAttorney;
	TerrainObject* pTerrainObject; //The TerrainObject that this area is part of
	TerrainObject* GetTerrainObject() const;
	CellCoordinates min;
	CellCoordinates max;
};
#endif _TerrainRectangularArea