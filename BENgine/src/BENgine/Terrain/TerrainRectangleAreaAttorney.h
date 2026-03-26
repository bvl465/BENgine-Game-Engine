//Ben La Monica
#pragma once
#ifndef _TerrainRectangleAreaAttorney
#define _TerrainRectangleAreaAttorney

#include "TerrainRectangleArea.h"

class TerrainRectangleAreaAttorney
{
public:
	class TRA
	{
	private:
		friend class TRAIterator;
		static TerrainObject* GetTerrainObject(TerrainRectangleArea* tra) { return tra->GetTerrainObject(); }
	};
};
#endif _TerrainRectangleAreaAttorney