#include "Sprite2DLayer.h"
#include "../BENgineSpriteBase.h"
//#include "../../Scene/SceneManager.h"
//#include "../../Scene/Scene.h"
#include "AzulCore.h"
#include "../BENgineSpriteBaseAttorney.h"

Sprite2DLayer::~Sprite2DLayer()
{
	for (auto it = drawMap.begin(); it != drawMap.end(); ++it)
	{
		BENgineSpriteBase* sprite = it->second;
		BENgineSpriteBaseAttorney::Layer::LayerErased(sprite);
	}
	drawMap.clear();
}
Sprite2DLayer::Sprite2DLayer(std::string name) : layerName(name)
{
	
}

std::string Sprite2DLayer::GetLayerName() const
{
	return std::string();
}

void Sprite2DLayer::ProcessDrawMap(Camera* cam)
{
	for (auto it = drawMap.begin(); it != drawMap.end(); ++it)
	{
		BENgineSpriteBase* sprite = it->second;
		sprite->Render(cam);
	}
}

void Sprite2DLayer::Register(const int priority, BENgineSpriteBase* sprite)
{
	//sprite->SetDrawMapStorageEntryRef(drawMap.insert(std::pair<int, BENgineSpriteBase*>(priority, sprite)));
	BENgineSpriteBaseAttorney::Layer::SetDrawMapStorageEntryRef(sprite, drawMap.insert(std::pair<int, BENgineSpriteBase*>(priority, sprite)));

}

void Sprite2DLayer::Deregister(DrawMapStorageEntryRef entryRef)
{
	if (entryRef != drawMap.end())
	{
		drawMap.erase(entryRef);
	}
}

void Sprite2DLayer::ChangePriority(DrawMapStorageEntryRef entryRef, const int newPriority)
{
	if (entryRef != drawMap.end())
	{
		BENgineSpriteBase* sprite = entryRef->second;
		drawMap.erase(entryRef);
		BENgineSpriteBaseAttorney::Layer::SetDrawMapStorageEntryRef(sprite, drawMap.insert(std::pair<int, BENgineSpriteBase*>(newPriority, sprite)));
	}
}
