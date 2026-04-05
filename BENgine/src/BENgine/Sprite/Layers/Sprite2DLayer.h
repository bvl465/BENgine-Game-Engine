//Ben La Monica
#pragma once
#ifndef _Sprite2DLayer
#define _Sprite2DLayer
#include <map>
#include <list>
#include <string>
class Camera;
class Sprite2DLayerManager;
class BENgineSpriteBase;
class Sprite2DLayer
{
private:
	using DrawMap = std::multimap<int, BENgineSpriteBase*>;
	DrawMap drawMap;
	std::string layerName;

public:

	friend class Sprite2DLayerAttorney;

	Sprite2DLayer() = default;
	Sprite2DLayer(const Sprite2DLayer&) = delete;
	Sprite2DLayer& operator=(const Sprite2DLayer&) = delete;
	~Sprite2DLayer();
	
	Sprite2DLayer(std::string name);	

	//Returns the name of the layer.
	std::string GetLayerName() const
	{
		return std::string();
	};

	using DrawMapStorageEntryRef = DrawMap::iterator;


private:
	void Register(const int priority, BENgineSpriteBase* sprite); //add to storageList

	void Deregister(DrawMapStorageEntryRef entryRef); //remove from storageList

	void ChangePriority(DrawMapStorageEntryRef entryRef, const int newPriority);

	void ProcessDrawMap(Camera* cam);

};
#endif _Sprite2DLayer