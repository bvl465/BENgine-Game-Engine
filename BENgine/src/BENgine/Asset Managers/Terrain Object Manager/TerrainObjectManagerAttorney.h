//Ben La Monica
#pragma once
#ifndef _TerrainObjectManagerAttorney
#define _TerrainObjectManagerAttorney

#include "TerrainObjectManager.h"

class TerrainObjectManagerAttorney
{

	friend class BENgine;

private:
	//Only BENgine can call the delete method for the TerrainManager
	static void Delete() { TerrainObjectManager::Delete(); }

};
#endif _TerrainObjectManagerAttorney