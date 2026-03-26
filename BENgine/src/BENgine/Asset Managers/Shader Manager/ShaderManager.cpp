//Ben La Monica
#include "ShaderManager.h"
#include "ShaderObject.h"

ShaderManager* ShaderManager::ptrInstance = nullptr;
//const std::string ShaderManager::defaultPath = "..\\Assets\\Shaders";

ShaderManager::ShaderManager() : defaultPath("../Assets/Shaders/")
{

}

void ShaderManager::Load(const std::string& key, const std::string& path)
{
	Instance().privLoad(key, path);
}

ShaderObject* ShaderManager::GetShaderObject(const std::string& key)
{
	return Instance().privGetShaderObject(key);
}

void ShaderManager::Delete()
{
	//Check if it is nullptr because there may be an instance where the user never uses a shader so this wouldn't be created
	//THAT BEING SAID... When the program stops running this is always called regardless as of 1/13/2025
	if (ptrInstance != nullptr) {
		std::map< std::string, ShaderObject*>::iterator itEnd = ptrInstance->storageMap.end();
		for (std::map< std::string, ShaderObject*>::iterator it = ptrInstance->storageMap.begin(); it != itEnd; ++it) {
			delete it->second;
		}
		//I use clear here instead of calling erase while iterating through because a map is set up as a red black tree and every time you
		//erase the tree rebalances. I would HOPE the implementation of erase is more efficient than that.
		ptrInstance->storageMap.clear();
		delete ptrInstance;
		ptrInstance = nullptr;
	}
}

//void ShaderManager::Initialize()
//{
//	//nothing for now..
//}

ShaderManager& ShaderManager::Instance()
{
	//part of singleton set up
	if (ptrInstance == nullptr) {
		ptrInstance = new ShaderManager();
		ptrInstance->privLoad(std::string("SpriteRender"), std::string("spriteRender")); //probably should go in an initialize
	}
	return *ptrInstance;
}

void ShaderManager::privLoad(const std::string& key, const std::string& path)
{
	std::map< std::string, ShaderObject*>::iterator it = storageMap.find(key);
	if (it != storageMap.end()) {
		//Using the same key multiple times throw an error
		throw std::invalid_argument("Key " + key + " is already used to define a ShaderObject.");
	}
	else {
		//Creates a ShaderObject and adds its pointer to the map with the specified key
		storageMap[key] = new ShaderObject((defaultPath + path).c_str()); //ShaderObject.h doesn't have any constructors with a std::string for its parameters.
	}
}

ShaderObject* ShaderManager::privGetShaderObject(const std::string& key) //returns a s
{
	std::map< std::string, ShaderObject*>::iterator it = storageMap.find(key);
	if (it == storageMap.end()) {
		//Key not in the storageMap
		throw std::invalid_argument("Key " + key + " could not be found.");
	}
	else {
		return it->second; //returns the ShaderObject
	}
}
