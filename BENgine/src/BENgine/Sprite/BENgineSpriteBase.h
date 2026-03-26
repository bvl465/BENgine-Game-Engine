#ifndef _BENgineSpriteBase
#define _BENgineSpriteBase

#include "AzulCore.h"
#include "./Layers/Sprite2DLayer.h"
#include "BENgineSpriteComponent.h"
#include <string>
class Camera;
class SpriteLayer2DCommandBase;
class Sprite2DLayer;
class BENgineSpriteBase : public BENgineSpriteComponent
{
public:
    BENgineSpriteBase() = default;
    BENgineSpriteBase(const BENgineSpriteBase&) = delete;
    BENgineSpriteBase& operator=(const BENgineSpriteBase&) = delete;
    virtual ~BENgineSpriteBase();


	//Definied by derived classes -------------------------------------------------------------------------------------------------

    virtual void SetCenter(const float x, const float y) = 0;

    virtual void SetScalePixel(const float x, const float y) = 0;

    virtual float GetCenterX() const = 0;

    virtual float GetCenterY() const = 0;

    virtual float GetWidth() const = 0;

    virtual float GetHeight() const = 0;

    virtual void SetScaleRotationTranslation(const float sx, const float sy, const float rad, const float px, const float py) = 0;

    //-----------------------------------------------------------------------------------------------------------------------------

    //Sets the priority of a sprite with in its layer. 
    //Parameters:
	//priority - the priority to set for this sprite in its layer. A higher number means higher priority. The higher the number the later it will be drawn.
	void SetLayerPriority(int priority);

	//Sets the current layer of the sprite to the layer passed in.
	//More efficient than setting the current layer via string if you already have a pointer to the layer since it doesn't involve having the Sprite2DLayerManager search for the layer.
	//Parameters:
	//layer - a pointer to the layer to set as the current layer of the sprite. Must not be nullptr.
	void SetCurrentLayer(Sprite2DLayer* layer);

	//Sets the current layer of the sprite to the layer with the name passed in.
	//Involves having the Sprite2DLayerManager search for the layer so it is less efficient than the version that takes a pointer if you already have a pointer to the layer.
	//Parameters:
	//layer - the name of the layer to set as the current layer of the sprite. The layer must already exist in the Sprite2DLayerManager of the current scene.
	void SetCurrentLayer(std::string layer);

	//Adds the sprite to its current layer. The sprite must have a current layer set before calling this method.
    void AddToCurrentLayer();

	//Removes the sprite from its current layer but does not clear the current layer.
	void RemoveFromLayer();

	//Adds the sprite to the layer passed in and sets the current layer to that layer. If the sprite is already in a layer then it is removed from that layer before being added to the new layer.
	//More efficient than adding to a layer via string if you already have a pointer to the layer since it doesn't involve having the Sprite2DLayerManager search for the layer.
	//Parameters:
	//layer - a pointer to the layer to add the sprite to. Must not be nullptr.
	void AddToLayer(Sprite2DLayer* layer);

	//Adds the sprite to the layer with the name passed in and sets the current layer to that layer. If the sprite is already in a layer then it is removed from that layer before being added to the new layer.
	//Involves having the Sprite2DLayerManager search for the layer so it is less efficient than the version that takes a pointer if you already have a pointer to the layer.
	//Parameters:
	//layer - the name of the layer to add the sprite to. The layer must already exist in the Sprite2DLayerManager of the current scene.
	void AddToLayer(std::string layer);


	//Returns a pointer to the layer this sprite is currently in. Returns nullptr if the sprite is not currently in a layer.
	Sprite2DLayer* GetLayerPtr() const;

	//Returns the priority of this sprite in the layer it is assigned to.
	int GetLayerPriority() const;

private:
	friend class BENgineSpriteBaseAttorney;
	//This is used for quick access and removal of the sprite in the draw map of the layer it is in.
	Sprite2DLayer::DrawMapStorageEntryRef drawMapStorageEntryRef;

	void SetDrawMapStorageEntryRef(Sprite2DLayer::DrawMapStorageEntryRef entryRef);

	void LayerErased();

    enum DrawLocation {

		//Sprite is in the draw map of ptr2DLayer and can be drawn by the layer.
        IN_DRAW_MAP,

		//Sprite has a ptr2DLayer but is not in the draw map of the layer and cannot be drawn by the layer.
        NOT_IN_DRAW_MAP,

		//Sprite is not assigned to a layer and cannot be drawn by any layer. ptr2DLayer should be nullptr in this state.
		LAYER_UNASSIGNED
    };
	DrawLocation drawLocation = LAYER_UNASSIGNED;

	//This is a pointer to the layer this sprite is assigned to.
	//It is set to nullptr if the sprite is not assigned to a layer.
	//This is used to avoid having to search for the sprite in the layer every time we need it.
	//This is set when the sprite is added to a layer and cleared when the sprite is removed from a layer.
	Sprite2DLayer* ptr2DLayer = nullptr;


	//The priority of this sprite in the layer it is assigned. Higher number = higher priority = drawn over more sprites in the layer it is in.
	int layerPriority = 0;
};

//TODO:
//Make SetDrawMapStorageEntryRef and LayerErased private and accessed by an attorney

#endif _BENgineSpriteBase