#pragma once
#ifndef _TRAIterator
#define _TRAIterator
//#include <iterator>
//#include "TerrainRectangleArea.h"
class TerrainRectangleArea;
#include "TerrainObject.h"
class TRAIterator
{
public:
    TRAIterator() = default;
	TRAIterator(const TRAIterator&) = default;
	TRAIterator& operator=(const TRAIterator&) = default;
	~TRAIterator() = default;
    TRAIterator(CellCoordinates coords, TerrainRectangleArea* area);

    TRAIterator operator++(int);

	CellMinMaxVects GetMinMaxVects() const;

	bool operator ==(const TRAIterator& compareWith); //If the Cell Coordinates match, returns true. If the Cell Coordinates do not match, return false.
	bool operator !=(const TRAIterator& compareWith); //If the Cell Coordinates do not match, returns true. If the Cell Coordinates match, return false.
private:
    CellCoordinates currentCoords;
    TerrainRectangleArea* terRectArea;


};
#endif _TRAIterator