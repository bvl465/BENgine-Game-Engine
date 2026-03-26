////Ben La Monica
//#pragma once
//#ifndef _Sprite2DLayerGroup
//#define _Sprite2DLayerGroup
//#include <list>
//#include <string>
//
//
//class Sprite2DLayer;
//class Sprite2DLayerGroup
//{
//private:
//	//this shouldn't be a list of strings instead it should use the from the layer manager
//	//otherwise it doesn't have any performance benefits. However, this still is more user friendly.
//	//The problem with giving the the layer group access to the iterators is that they would be
//	//modifying the contents of the map.
//	using LayerNameList = std::list<std::string>;
//
//	LayerNameList layerList;
//
//public:
//	Sprite2DLayerGroup() = default;
//	Sprite2DLayerGroup(const Sprite2DLayerGroup&) = delete;
//	Sprite2DLayerGroup& operator=(const Sprite2DLayerGroup&) = delete;
//	~Sprite2DLayerGroup();
//
//	void EnableLayerGroup();
//	void DisableLayerGroup();
//
//	void ClearLayerGroup();
//
//
//	void AddLayerToGroup(std::string layerName);
//	void RemoveLayerFromGroup(std::string layerName);
//
//
//};
//#endif _Sprite2DLayerGroup