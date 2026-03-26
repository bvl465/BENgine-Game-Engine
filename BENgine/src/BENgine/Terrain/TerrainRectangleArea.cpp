#include "TerrainRectangleArea.h"
#include "TRAIterator.h"
#include "../Game Object/Collidable/Collidable.h"
#include "../Collision/CollisionVolumeBSphere.h"


TerrainRectangleArea::TerrainRectangleArea(TerrainObject* terrain, CellCoordinates minimumCoord, CellCoordinates maximumCoord): min(minimumCoord), max(maximumCoord), pTerrainObject(terrain)
{

}

TerrainRectangleArea::TerrainRectangleArea(Collidable* collidable, TerrainObject* terrain) : pTerrainObject(terrain)
{
	const float radius = ((collidable->GetBSphere()).GetRadius());
	const Vect center = ((collidable->GetBSphere()).GetCenter());
	const Vect minimum = center - Vect(radius, radius, radius);
	const Vect maximum = center + Vect(radius, radius, radius);
	min = pTerrainObject->GetCellCoordinates(minimum.X(), minimum.Z());
	max = pTerrainObject->GetCellCoordinates(maximum.X(), maximum.Z());
}

CellCoordinates TerrainRectangleArea::GetMin() const
{
	return min;
}

CellCoordinates TerrainRectangleArea::GetMax() const
{
	return max;
}

TRAIterator TerrainRectangleArea::begin()
{
	return TRAIterator(min, this);
}

TRAIterator TerrainRectangleArea::end()
{
	return TRAIterator(max, this);
}

TerrainObject* TerrainRectangleArea::GetTerrainObject() const
{
	return pTerrainObject;
}
