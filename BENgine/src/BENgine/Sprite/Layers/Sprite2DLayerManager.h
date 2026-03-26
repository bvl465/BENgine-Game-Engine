//Ben La Monica
#pragma once
#ifndef _Sprite2DLayerManager
#define _Sprite2DLayerManager
#include <list>
#include <string>
#include <map>

class Sprite2DLayer;
class Sprite2DLayerManager
{
private:
	using LayerList = std::list<std::pair<bool, Sprite2DLayer*>>;
	using LayerListStorageEntryRef = LayerList::iterator;

	//Allows fast access to layers while maintaing the order of the list they were created in.
	using LayerReferenceMap = std::multimap<std::string, LayerListStorageEntryRef>;
	LayerList layerList;
	LayerReferenceMap layerReferenceMap;

	bool layersCreated = false;
	

public:
	Sprite2DLayerManager() = default;
	Sprite2DLayerManager(const Sprite2DLayerManager&) = delete;
	Sprite2DLayerManager& operator=(const Sprite2DLayerManager&) = delete;
	~Sprite2DLayerManager();

	//Creates layers with the given names and stores them in the order they were created.w
	//Parameters:
	//layerNames: A list of the names of the layers to create. The order of the list determines the order of the layers.
    void CreateLayers(std::list<std::string> layerNames);

	//Should be made private
	void ProcessElements();

	//Disables the layer with the given name from being drawn.
	//Parameters:
	//layerName: The name of the layer to disable.
	void DisableLayer(std::string layerName);

	//Enables the layer with the given name to be drawn.
	//Parameters:
	//layerName: The name of the layer to enable.
	void EnableLayer(std::string layerName);

	//Returns a pointer to the layer with the given name.
	//Parameters:
	//layerName: The name of the layer to return.
	Sprite2DLayer* GetLayer(std::string layerName);
	

};
#endif _Sprite2DLayerManager