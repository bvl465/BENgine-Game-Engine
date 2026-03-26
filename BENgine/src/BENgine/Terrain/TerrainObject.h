#pragma once
#ifndef _TerrainObject
#define _TerrainObject
#include "AzulCore.h"
//#include <tuple>
class Collidable;

struct Cell
{
	float Min; ///<The minimum height of the cell
	float Max; ///<The maximum height of the cell


	void set(float min, float max)
	{
		Min = min;
		Max = max;
	}

};

struct CellCoordinates
{
	int X; ///<The x coordinate of the cell in the TerrainObject
	int Z; ///<The z coordinate of the cell in the TerrainObject
	void set(int x, int z)
	{
		X = x;
		Z = z;
	}

};

struct CellMinMaxVects
{
	Vect Min; ///<The minimum point of the cell for xyz used to define an AABB
	Vect Max; ///<The maximum point of the cell for xyz used to define an AABB
	void set(Vect min, Vect max)
	{
		Min = min;
		Max = max;
	}
};

class TerrainObject
{

private:
	Model* pModTerrainObject; ///<The TerrainObject model
	GraphicsObject_TextureLight* pGObj_TerrainObject; ///<The textured render of the TerrainObject with lighting
	GraphicsObject_WireframeConstantColor* pGObj_TerrainObjectWireframe; ///<The wireframe render of the TerrainObject with constant color
	Vect* pNormals; ///<Stores the normals of the TerrainObject vertices.

	Cell* pCells; ///<stores the min and max height of each cell which is then used to calculate the cell's AABB
	//cells go in order of +x,-z to -x,+z

	const float len; ///<The length of the TerrainObject
	const float halfLen; ///<The half length of the TerrainObject, used to calculate the center of the TerrainObject and avoid division
	float cellSize; ///<The size of each cell in the TerrainObject
	float divCellSize;///< 1.f/cellSize; to avoid division by cellSize later in calculations
	float divSquaredCellSize; ///< 1.f / cellSize * cellSize; to avoid division by cellSize later in calculations
	int rowLength; ///<The number of cells in each row of the TerrainObject
	int nCells; ///<The number of cells in the TerrainObject 
	
	float GetVertexYFromModel(int ind) const; ///Returns y value of vertex a given index in the model
	int GetVertexIndex(int i, int j) const;
	
	const size_t pixel_width = 3; //The number of bytes per pixel in the heightmap texture
	
	int GetCellIndex(int x, int z) const;
	int GetCellIndexFromCoord(float xOrZ) const;
	
	int TexelIndex(int side, int i, int j) const;


public:
	TerrainObject(const char* heightmapFile, float length, float maxheight, float ytrans, Texture* tex, int RepeatU, int RepeatV);
	TerrainObject(const TerrainObject&) = delete;
	//TerrainObject(Model&&) = delete;
	TerrainObject& operator=(const TerrainObject&) & = delete;
	//TerrainObject& operator=(TerrainObject&&) & = delete;
	~TerrainObject();
	TerrainObject() = delete;
	//Returns the cell coordinates for a given position.
	//Cells go in order of +x,-z to -x,+z
	CellCoordinates GetCellCoordinates(float x, float z) const; 
	
	CellMinMaxVects GetCellMinMaxVects(CellCoordinates coordinates) const;


	//Used for visualization purposes
	void Intersect(Collidable* collidable);

	//
	void Render(Camera* camera);
	
	//Shows the point below the given position on the terrain object for visualization purposes.
	//Parameters:
	//pos - The position to show the point below of. The x and z values are used to determine the point below and the y value is ignored.
	void ShowPointBelow(Vect pos) const;

	//Returns the TerrainObject's model.
	Model* GetModel();

	//Returns the height of the terrain at the given position.
	//Parameters:
	//pos - The position to get the height at. The x and z values are used to determine the cell and the y value is ignored.
	float GetTerrainObjectHeight(Vect pos) const;

	//Returns how high the position is above the terrain. If the position is below the terrain then this will return a negative value.
	//Parameters:
	//pos - The position to get the height above terrain at.
	float GetHeightAboveTerrain(Vect pos) const;

	//Returns the normal of the terrain at the given position.
	//Parameters:
	//pos - The position to get the normal at. The x and z values are used to determine the cell and the y value is ignored.
	Vect GetTerrainObjectNormal(Vect pos) const;

	//Shows the cell that the position is located at for visualization purposes
	//Parameters:
	//pos - The position to show the cell of. The x and z values are used to determine the cell and the y value is ignored.
	void ShowCell(Vect pos) const;
};



#endif _TerrainObject