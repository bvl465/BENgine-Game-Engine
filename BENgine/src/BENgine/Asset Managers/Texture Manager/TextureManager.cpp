//Ben La Monica
#include "TextureManager.h"
#include "Texture.h"

TextureManager* TextureManager::ptrInstance = nullptr;
//const std::string TextureManager::defaultPath = "..\\Assets\\Textures";

TextureManager::TextureManager() : defaultPath("../Assets/Textures/")
{
	 
}

void TextureManager::Load(const std::string& key, const std::string& path)
{
	Instance().privLoad(key, path);
}

Texture* TextureManager::GetTexture(const std::string& key)
{
	return Instance().privGetTexture(key);
}

void TextureManager::Delete()
{
	//Check if it is nullptr because there may be an instance where the user never uses a texture so this wouldn't be created
	//THAT BEING SAID... When the program stops running this is always called regardless as of 1/13/2025
	if (ptrInstance != nullptr) {
		std::map< std::string, Texture*>::iterator itEnd = ptrInstance->storageMap.end();
		for (std::map< std::string, Texture*>::iterator it = ptrInstance->storageMap.begin(); it != itEnd; ++it) {
			delete it->second;
		}
		//I use clear here instead of calling erase while iterating through because a map is set up as a red black tree and every time you
		//erase the tree rebalances. I would HOPE the implementation of erase is more efficient than that.
		ptrInstance->storageMap.clear();
		delete ptrInstance;
		ptrInstance = nullptr;
	}
}


TextureManager& TextureManager::Instance()
{
	//part of singleton set up
	if (ptrInstance == nullptr) {
		ptrInstance = new TextureManager();
	}
	return *ptrInstance;
}

void TextureManager::privLoad(const std::string& key, const std::string& path)
{
	std::map< std::string, Texture*>::iterator it = storageMap.find(key);
	if (it != storageMap.end()) {
		//Using the same key multiple times throw an error
		throw std::invalid_argument("Key " + key + " is already used to define a Texture.");
	}
	else {
		//Creates a Texture and adds its pointer to the map with the specified key
		storageMap[key] = new Texture((defaultPath + path).c_str()); //Texture.h doesn't have any constructors with a std::string for its parameters.
	}
}

Texture* TextureManager::privGetTexture(const std::string& key) //returns a s
{
	std::map< std::string, Texture*>::iterator it = storageMap.find(key);
	if (it == storageMap.end()) {
		//Key not in the storageMap
		throw std::invalid_argument("Key " + key + " could not be found.");
	}
	else {
		return it->second; //returns the Texture
	}
}
