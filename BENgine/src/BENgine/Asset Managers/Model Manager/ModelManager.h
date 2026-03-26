//Ben La Monica
#pragma once
#ifndef _ModelManager
#define _ModelManager
#include <map>

#include "Model.h" //Use include instead of forward declaration in order to gain access to PreMadeModels enum


//Manages the creation, loading, retrieval, storage, and deletion of Models.
class ModelManager
{
public:
	friend class ModelManagerAttorney;

	//Creates a Model from the .azul file at specified path and then loads the Model into the storageMap with key passed.
	// Parameters:
	// key - The key to associate with the Model in the storageMap. (Must be unique)
	// path - The file path of the .azul file to create the Model from.
	static void Load(const std::string& key, const std::string& path);

	//Creates a plane with a side length of planeXZ and the UV coordinates passed and then loads the Model into the storageMap with key passed.
	//Parameters:
	//key - The key to associate with the Model in the storageMap. (Must be unique)
	//planeXZ - The length of the sides of the plane in the X and Z directions.
	//u - number of times to repeat the texture in the U direction.
	//v - number of times to repeat the texture in the V direction.
	static void Load(const std::string& key, int planeXZ, int u, int v);

	//Creates a Model of one of the PreMadeModels defined in Model.h and then loads the Model into the storageMap with key passed.
	// Parameters:
	// key - The key to associate with the Model in the storageMap. (Must be unique)
	// preMadeModel - The PreMadeModel to create a Model of.
	static void Load(const std::string& key, const Model::PreMadeModels preMadeModel);
	
	//Searches the storageMap for key and returns a pointer to the Model associated with that key.
	// Parameters:
	// key - The key assoiated with the Model to search for in the storageMap.
	static Model* GetModel(const std::string& key);

private:

	ModelManager();
	ModelManager(const ModelManager&) = delete;
	ModelManager& operator=(const ModelManager&) = delete;
	~ModelManager() = default;
	static ModelManager& Instance(); // Access reference (all public methods will be static)

	//Deletes the instance of the ModelManager and all Models stored in the storageMap. Accessed by BENgine through ModelManagerAttorney.
	static void Delete();


	void privLoad(const std::string& key, const std::string& path);

	void privLoad(const std::string& key, int planeXZ, int u, int v);

	void privLoad(const std::string& key, const Model::PreMadeModels preMadeModel);
	
	Model* privGetModel(const std::string& key);

	
	static ModelManager* ptrInstance;

	//The file path for the root folder azul models are stored in.
	const std::string defaultPath;

	//Map that Models are loaded into and retrieved from. The key is the name the user assigns the Model, and the value is a pointer to the Model.
	std::map<std::string, Model*> storageMap;


};
#endif _ModelManager