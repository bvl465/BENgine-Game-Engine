#include "Sprite2DLayerManager.h"
#include "Sprite2DLayer.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/Scene.h"
#include "Sprite2DLayerAttorney.h"

void Sprite2DLayerManager::CreateLayers(std::list<std::string> layerNames)
{
	assert(layersCreated == false);
	for (auto it = layerNames.begin(); it != layerNames.end(); ++it)
	{
		Sprite2DLayer* layer = new Sprite2DLayer(*it);

		//LayerListStorageEntryRef entryRef = layerList.insert(layerList.end(), std::pair<std::string, std::pair<bool, Sprite2DLayer*>>(*it, std::pair<bool, Sprite2DLayer*>(true, layer)));
		LayerListStorageEntryRef entryRef = layerList.insert(layerList.end(), std::pair<bool, Sprite2DLayer*>(std::pair<bool, Sprite2DLayer*>(true, layer)));
		layerReferenceMap.insert(std::pair<std::string, LayerListStorageEntryRef>(*it, entryRef));
	}
	layersCreated = true;
}

void Sprite2DLayerManager::ProcessElements()
{

	//TODO come up with a more elegant solution to checking if layers are created every time.
	//Maybe use a strategy pattern in Scene::Draw() where one strategy is used before layers
	//are created and another is used after a Scene::CreateLayers(std::list<std::string> layerNames) is called.
	//Have the strategy used before layers are created not call this method at all.
	if (layersCreated == true)
	{
		Camera* cam = (SceneManager::GetCurrentScene())->GetCurrentCamera2D();
		for (auto it = layerList.begin(); it != layerList.end(); ++it)
		{
			//if (it->second.first == true)
			//{
			//	it->second.second->ProcessDrawMap();
			//}

			if (it->first == true)
			{
				Sprite2DLayerAttorney::Draw::ProcessDrawMap(it->second, cam);
			}
		}
	}

}

void Sprite2DLayerManager::DisableLayer(std::string layerName)
{
	auto it = layerReferenceMap.find(layerName);
	assert(it != layerReferenceMap.end());
	//(it->second)->second.first = false;
	(it->second)->first = false;

}

void Sprite2DLayerManager::EnableLayer(std::string layerName)
{
	auto it = layerReferenceMap.find(layerName);
	assert(it != layerReferenceMap.end());
	//(it->second)->second.first = true;
	(it->second)->first = true;
}

Sprite2DLayer* Sprite2DLayerManager::GetLayer(std::string layerName)
{
	auto it = layerReferenceMap.find(layerName);
	assert(it != layerReferenceMap.end());
	
	return (it->second)->second;
}

Sprite2DLayerManager::~Sprite2DLayerManager()
{
	for (auto it = layerList.begin(); it != layerList.end(); ++it)
	{
		//delete it->second.second;
		delete it->second;
	}
	layerList.clear();
	layerReferenceMap.clear();
}
