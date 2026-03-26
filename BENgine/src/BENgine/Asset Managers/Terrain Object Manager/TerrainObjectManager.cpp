//Ben La Monica
#include "TerrainObjectManager.h"
#include "../../Terrain/TerrainObject.h"
#include "Texture.h"
//#include "../../Terrain/TerrainObject.h"
TerrainObjectManager* TerrainObjectManager::ptrInstance = nullptr;
//const std::string TerrainObjectManager::defaultPath = "..\\Assets\\TerrainObjects";

TerrainObjectManager::TerrainObjectManager() : defaultPath("../Assets/Height Maps/")
{

}

void TerrainObjectManager::Load(const std::string key, const std::string heightMapPath, float length, float maxHeight, float ytrans, Texture* texture, int RepeatU, int RepeatV)
{
	Instance().privLoad(key, heightMapPath, length, maxHeight, ytrans, texture, RepeatU, RepeatV);
}



TerrainObject* TerrainObjectManager::GetTerrainObject(const std::string& key)
{
	return Instance().privGetTerrainObject(key);
}

void TerrainObjectManager::Delete()
{
	//Check if it is nullptr because there may be an instance where the user never uses a TerrainObject so this wouldn't be created
	//THAT BEING SAID... When the program stops running this is always called regardless as of 1/13/2025
	if (ptrInstance != nullptr) {
		std::map< std::string, TerrainObject*>::iterator itEnd = ptrInstance->storageMap.end();
		for (std::map< std::string, TerrainObject*>::iterator it = ptrInstance->storageMap.begin(); it != itEnd; ++it) {
			delete it->second;
		}
		//I use clear here instead of calling erase while iterating through because a map is set up as a red black tree and 
		// every time you erase the tree rebalances. I would HOPE the implementation of erase is more efficient than that
		// but I have yet to check.
		//     /\   /\
		//    |  | |  |      Wake up, Ben...
		//     \ --- /       The Matrix has you...
		//    / | _ | \      Don't follow the white rabbit...
		//    \(= X =)/      Knock, knock, Ben.
		//     '~~~~~'
		//     / L_ \`\
		//   (\`~._)(_/
		//    (..)_; )_
		//    '--' `---'

		ptrInstance->storageMap.clear();
		delete ptrInstance;
		ptrInstance = nullptr;
	}
}

//void TerrainObjectManager::Initialize()
//{
//	//Maybe put any TerrainObjects that need to be pre loaded in here. 
//}

TerrainObjectManager& TerrainObjectManager::Instance()
{
	//part of singleton set up
	if (ptrInstance == nullptr) {
		ptrInstance = new TerrainObjectManager();
	}
	return *ptrInstance;
}

void TerrainObjectManager::privLoad(const std::string key, const std::string heightMapPath, float length, float maxHeight, float ytrans, Texture* texture, int RepeatU, int RepeatV)
{
	std::map< std::string, TerrainObject*>::iterator it = storageMap.find(key);
	if (it != storageMap.end()) {
		//Using the same key multiple times throw an error
		throw std::invalid_argument("Key " + key + " is already used to define a TerrainObject.");
	}
	else {
		//Creates a TerrainObject and adds its pointer to the map with the specified key
		storageMap[key] = new TerrainObject((defaultPath + heightMapPath).c_str(), length, maxHeight, ytrans, texture, RepeatU, RepeatV); //TerrainObject.h doesn't have any constructors with a std::string for its parameters.
	}
}



//void TerrainObjectManager::privLoad(const std::string& key, const TerrainObject::PreMadeTerrainObjects preMadeTerrainObject)
//{
//	std::map< std::string, TerrainObject*>::iterator it = storageMap.find(key);
//	if (it != storageMap.end()) {
//		//Using the same key multiple times throw an error
//		throw std::invalid_argument("Key " + key + " is already used to define a TerrainObject.");
//	}
//	else {
//		//Creates a TerrainObject and adds its pointer to the map with the specified key
//		storageMap[key] = new TerrainObject(preMadeTerrainObject);
//	}
//}

TerrainObject* TerrainObjectManager::privGetTerrainObject(const std::string& key) //returns a s
{
	std::map< std::string, TerrainObject*>::iterator it = storageMap.find(key);
	if (it == storageMap.end()) {
		//Key not in the storageMap
		throw std::invalid_argument("Key " + key + " could not be found.");
	}
	else {
		return it->second; //returns the TerrainObject
	}
}
