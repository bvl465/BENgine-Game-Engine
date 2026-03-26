#include "BENgineSpriteBase.h"
#include "./Layers/Sprite2DLayer.h"
#include "./Layers/Sprite2DLayerManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneAttorney.h"
#include "./Layers/Sprite2DLayerAttorney.h"
void BENgineSpriteBase::SetDrawMapStorageEntryRef(Sprite2DLayer::DrawMapStorageEntryRef entryRef)
{
	drawMapStorageEntryRef = entryRef;
	drawLocation = IN_DRAW_MAP;
}

void BENgineSpriteBase::SetLayerPriority(int priority)
{

	if (drawLocation != IN_DRAW_MAP)
	{
		layerPriority = priority;
	}
	else
	{
		Sprite2DLayerAttorney::SpriteBase::ChangePriority(ptr2DLayer, drawMapStorageEntryRef, priority);
		layerPriority = priority;
	}
}

void BENgineSpriteBase::SetCurrentLayer(Sprite2DLayer* layer)
{
	assert(layer != nullptr);
	if (drawLocation != IN_DRAW_MAP)
	{
		ptr2DLayer = layer;
		drawLocation = NOT_IN_DRAW_MAP;
	}
	else
	{

		Sprite2DLayerAttorney::SpriteBase::Deregister(ptr2DLayer, drawMapStorageEntryRef);
		ptr2DLayer = layer;
		drawLocation = NOT_IN_DRAW_MAP;
	}
}

void BENgineSpriteBase::SetCurrentLayer(std::string layer)
{
	Sprite2DLayer* tempLayer = (SceneAttorney::Layer::GetSprite2DLayerManager(SceneManager::GetCurrentScene()))->GetLayer(layer);
	assert(tempLayer != nullptr);
	if (drawLocation != IN_DRAW_MAP)
	{
		ptr2DLayer = tempLayer;
		drawLocation = NOT_IN_DRAW_MAP;
	}
	else
	{
		Sprite2DLayerAttorney::SpriteBase::Deregister(ptr2DLayer, drawMapStorageEntryRef);
		ptr2DLayer = tempLayer;
		drawLocation = NOT_IN_DRAW_MAP;
	}
}

void BENgineSpriteBase::AddToCurrentLayer()
{
	assert(drawLocation != LAYER_UNASSIGNED);

	if (drawLocation == NOT_IN_DRAW_MAP)
	{
		Sprite2DLayerAttorney::SpriteBase::Register(ptr2DLayer, layerPriority, this);		
	}
}

void BENgineSpriteBase::RemoveFromLayer()
{
	if (drawLocation == IN_DRAW_MAP)
	{
		Sprite2DLayerAttorney::SpriteBase::Deregister(ptr2DLayer, drawMapStorageEntryRef);

		drawLocation = NOT_IN_DRAW_MAP;
	}
}

void BENgineSpriteBase::AddToLayer(Sprite2DLayer* layer)
{
	assert(layer != nullptr);
	
	if (drawLocation != IN_DRAW_MAP)
	{
		ptr2DLayer = layer;
		Sprite2DLayerAttorney::SpriteBase::Register(layer, layerPriority, this);
	}
	else
	{
		Sprite2DLayerAttorney::SpriteBase::Deregister(ptr2DLayer, drawMapStorageEntryRef);
		drawLocation = NOT_IN_DRAW_MAP;
		ptr2DLayer = layer;
		Sprite2DLayerAttorney::SpriteBase::Register(layer, layerPriority, this);

	}

}

void BENgineSpriteBase::AddToLayer(std::string layer)
{
	Sprite2DLayer* tempLayer = (SceneAttorney::Layer::GetSprite2DLayerManager(SceneManager::GetCurrentScene()))->GetLayer(layer);
	assert(tempLayer != nullptr);

	if (drawLocation != IN_DRAW_MAP)
	{
		ptr2DLayer = tempLayer;
		Sprite2DLayerAttorney::SpriteBase::Register(tempLayer, layerPriority, this);

	}
	else
	{
		Sprite2DLayerAttorney::SpriteBase::Deregister(ptr2DLayer, drawMapStorageEntryRef);
		drawLocation = NOT_IN_DRAW_MAP;
		ptr2DLayer = tempLayer;
		Sprite2DLayerAttorney::SpriteBase::Register(tempLayer, layerPriority, this);
	}
}

void BENgineSpriteBase::LayerErased()
{
	ptr2DLayer = nullptr;
	drawLocation = LAYER_UNASSIGNED;
}

Sprite2DLayer* BENgineSpriteBase::GetLayerPtr() const
{
	return ptr2DLayer;
}

int BENgineSpriteBase::GetLayerPriority() const
{
	return layerPriority;
}

BENgineSpriteBase::~BENgineSpriteBase()
{
	if (drawLocation == IN_DRAW_MAP)
	{
		Sprite2DLayerAttorney::SpriteBase::Deregister(ptr2DLayer, drawMapStorageEntryRef);

		drawLocation = NOT_IN_DRAW_MAP;
	}
}
