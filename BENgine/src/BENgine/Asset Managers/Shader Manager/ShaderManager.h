//Ben La Monica
#pragma once
#ifndef _ShaderManager
#define _ShaderManager
#include <map>
class ShaderObject;

//Manages the creation, loading, retrieval, storage, and deletion of ShaderObjects.
class ShaderManager
{
public:
	friend class ShaderManagerAttorney;

	//Creates a ShaderObject from the file at specified path and then loads the ShaderObject into the storageMap with key passed.
	// Parameters:
	// key - The key to associate with the ShaderObject in the storageMap. (Must be unique)
	// path - The file path of the file to create the ShaderObject from.
	static void Load(const std::string& key, const std::string& path);

	//Searches the storageMap for key and returns a pointer to the ShaderObject associated with that key.
	// Parameters:
	// key - The key associated the ShaderObject dto search for in the storageMap.
	static ShaderObject* GetShaderObject(const std::string& key); 

private:
	ShaderManager();
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator=(const ShaderManager&) = delete;
	~ShaderManager() = default;

	static ShaderManager& Instance();

	//Deletes the instance of the ShaderManager and all ShaderObjects stored in the storageMap. Accessed by BENgine through ShaderManagerAttorney.
	static void Delete();

	void privLoad(const std::string& key, const std::string& path);

	ShaderObject* privGetShaderObject(const std::string& key);

	static ShaderManager* ptrInstance;

	//The file path for the root folder shader files are stored in.
	const std::string defaultPath;

	//Map that ShaderObjects are loaded into and retrieved from. The key is the name the user assigns the ShaderObject, and the value is a pointer to the ShaderObject.
	std::map<std::string, ShaderObject*> storageMap;


};
#endif _ShaderManager