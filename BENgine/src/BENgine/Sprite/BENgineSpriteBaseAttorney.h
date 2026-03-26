//Ben La Monica
#pragma once
#ifndef _BENgineSpriteBaseAttorney
#define _BENgineSpriteBaseAttorney

#include "BENgineSpriteBase.h"

class BENgineSpriteBaseAttorney
{
public:
	class Layer
	{
		friend class Sprite2DLayer;
	private:
		static void SetDrawMapStorageEntryRef(BENgineSpriteBase* sprite, Sprite2DLayer::DrawMapStorageEntryRef entryRef) { sprite->SetDrawMapStorageEntryRef(entryRef); }

		static void LayerErased(BENgineSpriteBase* sprite) { sprite->LayerErased(); }
	};

};
#endif _BENgineSpriteBaseAttorney