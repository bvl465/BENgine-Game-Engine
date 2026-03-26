//Ben La Monica
#pragma once
#ifndef _Sprite2DLayerAttorney
#define _Sprite2DLayerAttorney

#include "Sprite2DLayer.h"

class Sprite2DLayerAttorney
{
public:
	class SpriteBase
	{
		friend class BENgineSpriteBase;
	private:
		static void Register(Sprite2DLayer* layer, const int priority, BENgineSpriteBase* sprite) { layer->Register(priority, sprite); }
		static void Deregister(Sprite2DLayer* layer, Sprite2DLayer::DrawMapStorageEntryRef entryRef) { layer->Deregister(entryRef); }
		static void ChangePriority(Sprite2DLayer* layer, Sprite2DLayer::DrawMapStorageEntryRef entryRef, const int newPriority) { layer->ChangePriority(entryRef, newPriority); }
	};
public:
	class Draw
	{
		friend class Sprite2DLayerManager;
	private:
		static void ProcessDrawMap(Sprite2DLayer* layer, Camera* cam) { layer->ProcessDrawMap(cam); }
	};
};
#endif _Sprite2DLayerAttorney