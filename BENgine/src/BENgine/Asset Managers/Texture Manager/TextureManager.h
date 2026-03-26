//Ben La Monica
#pragma once
#ifndef _TextureManager
#define _TextureManager
#include <map>
class Texture;

//Manages the creation, loading, retrieval, storage, and deletion of Textures.
class TextureManager
{
public:
	friend class TextureManagerAttorney;


	//Creates a Texture from the file at specified path and then loads the Texture into the storageMap with key passed.
	// Parameters:
	// key - The key to associate with the Texture in the storageMap. (Must be unique)
	// path - The file path of the file to create the Texture from.
	static void Load(const std::string& key, const std::string& path);

	//Searches the storageMap for key and returns a pointer to the Texture associated with that key.
	// Parameters:
	// key - The key associated the Texture to search for in the storageMap.
	static Texture* GetTexture(const std::string& key);

	//static void Initialize(); //empty for now


private:
	TextureManager();
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	~TextureManager() = default;

	static TextureManager& Instance(); 

	//Deletes the instance of the TextureManager and all Textures stored in the storageMap. Accessed by BENgine through TextureManagerAttorney.
	static void Delete();

	void privLoad(const std::string& key, const std::string& path);

	Texture* privGetTexture(const std::string& key);

	static TextureManager* ptrInstance;

	//The file path for the root folder texture files are stored in.
	const std::string defaultPath;

	//Map that Textures are loaded into and retrieved from. The key is the name the user assigns the Texture, and the value is a pointer to the Texture.
	std::map<std::string, Texture*> storageMap;


};
#endif _TextureManager