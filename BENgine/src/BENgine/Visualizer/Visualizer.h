//Ben La Monica
#pragma once
#ifndef _Visualizer
#define _Visualizer

#include "AzulCore.h"
#include "Vect.h"
#include <list>
#include <queue>
class GraphicsObject_WireframeConstantColor;
class Matrix;
class Model;
class VisualizerCommandPool;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class VisualizerCommandBase;
class CollisionVisualizerBSphereCommand;
class CollisionVisualizerAABBCommand;
class CollisionVisualizerOBBCommand;
class Visualizer : public Align16
{
private:

	friend class VisualizerAttorney;
    Visualizer();
    Visualizer(const Visualizer&) = delete;
    Visualizer& operator=(const Visualizer&) = delete;
    ~Visualizer() = default;

    static Visualizer& Instance();
    static void Delete();

    //BSPHERE
	static void RenderBSphere(Matrix& S, const Vect& col);
    void privRenderBSphere(Matrix& S, const Vect& col);

	static void ReturnBSphereCommand(CollisionVisualizerBSphereCommand* cmd);
	void privReturnBSphereCommand(CollisionVisualizerBSphereCommand* cmd);
	void privShowBSphere(const CollisionVolumeBSphere& S, const Vect& col);

    //AABB
    static void RenderAABB(Matrix& aabb, const Vect& col);
    void privRenderAABB(Matrix& aabb, const Vect& col);

    static void ReturnAABBCommand(CollisionVisualizerAABBCommand* cmd);
    void privReturnAABBCommand(CollisionVisualizerAABBCommand* cmd);
    void privShowAABB(const CollisionVolumeAABB& aabb, const Vect& col);
    void privShowAABBUsingMinMax(const Vect min, const Vect max, const Vect& col);

    //OBB
	static void RenderOBB(Matrix& obb, const Vect& col);
	void privRenderOBB(Matrix& obb, const Vect& col);
    static void ReturnOBBCommand(CollisionVisualizerOBBCommand* cmd);
    void privReturnOBBCommand(CollisionVisualizerOBBCommand* cmd);
    void privShowOBB(const CollisionVolumeOBB& obb, const Vect& col);

    void privShowVectorFromPoint(const Vect& startingPos, const Vect& direction, const Vect& color, const float width);

	void privShowMarker(const Vect& pos, const Vect& col);

    static Visualizer* ptrInstance;
    GraphicsObject_WireframeConstantColor* WFUnitSphere;
    GraphicsObject_WireframeConstantColor* WFUnitBox;
    static Vect DEFAULT_COLOR;
    using CommandList = std::list<VisualizerCommandBase*>;
    CommandList cmdList;
	static VisualizerCommandPool* cmdPool;

    //Called by BENgine and executes all the visualizer commands.
    static void VisualizeAll();

	//Called by VisualizeAll and executes all the visualizer commands.
	void privVisualizeAll();

public:


	//Renders a wireframe of the CollisionVolumeBSphere in the color passed
	//Parameters:
	//bSphere - The CollisionVolumeBSphere that will be visualized
	//color - The color that the bounding sphere will be rendered in
    static void ShowBSphere(const CollisionVolumeBSphere& bSphere, const Vect& color);

	//Renders a wireframe of the CollisionVolumeAABB in the color passed
	//Parameters:
	//aabb - The CollisionVolumeAABB that will be visualized
	//color - The color that the bounding box will be rendered in
    static void ShowAABB(const CollisionVolumeAABB& aabb, const Vect& color);

	//Renders a wireframe of an AABB using the min and max points of the box and the color passed
	//Parameters:
	//min - The minimum point of the AABB that will be visualized
	//max - The maximum point of the AABB that will be visualized
	//color - The color that the bounding box will be rendered in
    static void ShowAABBUsingMinMax(const Vect min, const Vect max, const Vect& color);

	//Renders a wireframe of the CollisionVolumeOBB in the color passed
	//Parameters:
	//obb - The CollisionVolumeOBB that will be visualized
	//color - The color that the bounding box will be rendered in
    static void ShowOBB(const CollisionVolumeOBB& obb, const Vect& color);

	//Shows a marker at the position passed in the color passed
	//Parameters:
	//pos - The position that the marker will be rendered at
	//color - The color that the marker will be rendered in
	static void ShowMarker(const Vect& pos, const Vect& color);

	//Shows a vector starting at the position passed in the direction passed in the color passed
	//Parameters:
	//startingPos - The position that the vector will start at
	//direction - The direction that the vector will point in
	//color - The color that the vector will be rendered in
	//width - The width of the vector line
    static void ShowVectorFromPoint(const Vect& startingPos, const Vect& direction, const Vect& color, const float width);
};

#endif _Visualizer