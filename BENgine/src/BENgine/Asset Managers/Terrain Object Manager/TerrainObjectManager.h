//Ben La Monica
#pragma once
#ifndef _TerrainObjectManager
#define _TerrainObjectManager
#include <map>

//#include "../TerrainObject.h" //Use include instead of forward declaration in order to gain access to PreMadeTerrainObjects
class TerrainObject;
class Texture;

//Manages the creation, loading, retrieval, storage, and deletion of TerrainObjects.
class TerrainObjectManager
{
public:
	friend class TerrainObjectManagerAttorney;

	//Creates a TerrainObject from the height map file at specified path using the provided parameters and then loads the TerrainObject into the storageMap with key passed.
	// Parameters:
	// key - The key to associate with the TerrainObject in the storageMap. (Must be unique)
	// heightMapPath - The file path of the height map file to create the TerrainObject from.
	// length - The length of the sides of the TerrainObject in the X and Z directions.
	// maxHeight - The maximum height of the TerrainObject in the Y direction from bottom to top.
	// ytrans - The value to translate the terrain in the Y direction.
	// texture - The Texture to apply to the TerrainObject. (Can't be nullptr)
	// RepeatU - The number of times to repeat the texture in the U direction.
	// RepeatV - The number of times to repeat the texture in the V direction.
	static void Load(const std::string key, const std::string heightMapPath, float length, float maxHeight, float ytrans, Texture* texture, int RepeatU, int RepeatV); //used for files

	//static void Load(const std::string& key, const TerrainObject::PreMadeTerrainObjects preMadeTerrainObject);  //used for PreMadeTerrainObjects

	//Searches the storageMap for key and returns a pointer to the TerrainObject associated with that key.
	// Parameters:
	// key - The key assoiated with the TerrainObject to search for in the storageMap.
	static TerrainObject* GetTerrainObject(const std::string& key);

	//static void Initialize(); //empty for now




private:

	TerrainObjectManager();
	TerrainObjectManager(const TerrainObjectManager&) = delete;
	TerrainObjectManager& operator=(const TerrainObjectManager&) = delete;
	~TerrainObjectManager() = default;

	static TerrainObjectManager& Instance(); // Access reference (all public methods will be static)

	//Deletes the instance of the TerrainObjectManager and all TerrainObjects stored in the storageMap. Accessed by BENgine through TerrainObjectManagerAttorney.
	static void Delete();

	void privLoad(const std::string key, const std::string heightMapPath, float length, float maxHeight, float ytrans, Texture* texture, int RepeatU, int RepeatV);


	//void privLoad(const std::string& key, const TerrainObject::PreMadeTerrainObjects preMadeTerrainObject);

	TerrainObject* privGetTerrainObject(const std::string& key);

	static TerrainObjectManager* ptrInstance;

	//The file path for the root folder terrain object height maps are stored in.
	const std::string defaultPath;

	//Map that TerrainObjects are loaded into and retrieved from. The key is the name the user assigns the TerrainObject, and the value is a pointer to the TerrainObject.
	std::map<std::string, TerrainObject*> storageMap;


};
#endif _TerrainObjectManager