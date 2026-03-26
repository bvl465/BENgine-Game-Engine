//Ben La Monica
#include "ModelManager.h"

ModelManager* ModelManager::ptrInstance = nullptr;

ModelManager::ModelManager() : defaultPath("../Assets/Models/")
{

}

void ModelManager::Load(const std::string& key, const std::string& path)
{
	Instance().privLoad(key, path);
}

void ModelManager::Load(const std::string& key, int planeXZ, int u, int v)
{
	Instance().privLoad(key, planeXZ, u, v);
}

void ModelManager::Load(const std::string& key, const Model::PreMadeModels preMadeModel)
{
	Instance().privLoad(key, preMadeModel);
}

Model* ModelManager::GetModel(const std::string& key)
{
	return Instance().privGetModel(key);
}

void ModelManager::Delete()
{
	if (ptrInstance != nullptr) {
		std::map< std::string, Model*>::iterator itEnd = ptrInstance->storageMap.end();
		for (std::map< std::string, Model*>::iterator it = ptrInstance->storageMap.begin(); it != itEnd; ++it) {
			delete it->second;
		}

		ptrInstance->storageMap.clear();
		delete ptrInstance;
		ptrInstance = nullptr;
	}
}

//void ModelManager::Initialize()
//{
//	//Maybe put any models that need to be pre loaded in here. 
//}

ModelManager& ModelManager::Instance()
{
	//part of singleton set up
	if (ptrInstance == nullptr) {
		ptrInstance = new ModelManager();
		ptrInstance->privLoad(std::string("UnitSquareXY"), Model::PreMadeModels::UnitSquareXY); //pre load because it is used by the sprite
	}
	return *ptrInstance;
}

void ModelManager::privLoad(const std::string& key, const std::string& path)
{
	std::map< std::string, Model*>::iterator it = storageMap.find(key);
	if (it != storageMap.end()) {
		//Using the same key multiple times throw an error
		throw std::invalid_argument("Key " + key + " is already used to define a Model.");
	}
	else {
		//Creates a Model and adds its pointer to the map with the specified key
		storageMap[key] = new Model((defaultPath + path).c_str()); //Model.h doesn't have any constructors with a std::string for its parameters.
	}
}

void ModelManager::privLoad(const std::string& key, int planeXZ, int u, int v)
{
	std::map< std::string, Model*>::iterator it = storageMap.find(key);
	if (it != storageMap.end()) {
		//Using the same key multiple times throw an error
		throw std::invalid_argument("Key " + key + " is already used to define a Model.");
	}
	else {
		//Creates a Model and adds its pointer to the map with the specified key
		storageMap[key] = new Model(planeXZ, u, v);
	}
}



void ModelManager::privLoad(const std::string& key, const Model::PreMadeModels preMadeModel)
{
	std::map< std::string, Model*>::iterator it = storageMap.find(key);
	if (it != storageMap.end()) {
		//Using the same key multiple times throw an error
		throw std::invalid_argument("Key " + key + " is already used to define a Model.");
	}
	else {
		//Creates a Model and adds its pointer to the map with the specified key
		storageMap[key] = new Model(preMadeModel);
	}
}

Model* ModelManager::privGetModel(const std::string& key) //returns a s
{
	std::map< std::string, Model*>::iterator it = storageMap.find(key);
	if (it == storageMap.end()) {
		//Key not in the storageMap
		throw std::invalid_argument("Key " + key + " could not be found.");
	}
	else {
		return it->second; //returns the Model
	}
}
