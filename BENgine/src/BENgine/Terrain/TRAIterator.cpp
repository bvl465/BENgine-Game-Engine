#include "TRAIterator.h"
#include "TerrainRectangleArea.h"
#include "TerrainRectangleAreaAttorney.h"
TRAIterator::TRAIterator(CellCoordinates ind, TerrainRectangleArea* area) : terRectArea(area), currentCoords(ind)
{

	//Initialize the iterator with a pointer to the TerrainRectangleArea to access the min and max indices and the TerrainObject
}

TRAIterator TRAIterator::operator++(int)
{
	CellCoordinates maxCoords = terRectArea->GetMax();
	CellCoordinates minCoords = terRectArea->GetMin();
	//Increment the iterator
	if (currentCoords.X >= maxCoords.X) {
		currentCoords.X -= 1;
	}
	else{
		currentCoords.X = minCoords.X;
		currentCoords.Z  += 1;
	}
	return *this; //Return the incremented iterator
}

CellMinMaxVects TRAIterator::GetMinMaxVects() const
{
    return (TerrainRectangleAreaAttorney::TRA::GetTerrainObject(terRectArea))->GetCellMinMaxVects(currentCoords);
}

bool TRAIterator::operator==(const TRAIterator& compareWith)
{
    if (currentCoords.X == compareWith.currentCoords.X && currentCoords.Z == compareWith.currentCoords.Z) {
        return true;
    }
    return false;
}

bool TRAIterator::operator!=(const TRAIterator& compareWith)
{
	if (currentCoords.X != compareWith.currentCoords.X || currentCoords.Z != compareWith.currentCoords.Z) {
		return true;
	}
	return false;
}
