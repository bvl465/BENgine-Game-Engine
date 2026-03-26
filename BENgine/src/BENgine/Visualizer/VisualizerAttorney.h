//Ben La Monica
#pragma once
#ifndef _VisualizerAttorney
#define _VisualizerAttorney

#include "Visualizer.h"

class VisualizerAttorney
{
public:
	class GameLoop
	{
		friend class BENgine;
	private:
		static void VisualizeAll() { Visualizer::VisualizeAll(); }
		static void Delete() { Visualizer::Delete(); }
	};

public:
	class Commands
	{
		friend class CollisionVisualizerBSphereCommand;

	private:

		static void RenderBSphere(Matrix& S, const Vect& col) { Visualizer::RenderBSphere(S, col); }
		static void ReturnBSphereCommand(CollisionVisualizerBSphereCommand* cmd) { Visualizer::ReturnBSphereCommand(cmd); }

	};

	class AABBCommands
	{
		friend class CollisionVisualizerAABBCommand;

	private:

		static void RenderAABB(Matrix& S, const Vect& col) { Visualizer::RenderAABB(S, col); }
		static void ReturnAABBCommand(CollisionVisualizerAABBCommand* cmd) { Visualizer::ReturnAABBCommand(cmd); }

	};
	class OBBCommands
	{
		friend class CollisionVisualizerOBBCommand;

	private:

		static void RenderOBB(Matrix& S, const Vect& col) { Visualizer::RenderOBB(S, col); }
		static void ReturnOBBCommand(CollisionVisualizerOBBCommand* cmd) { Visualizer::ReturnOBBCommand(cmd); }

	};

};
#endif _VisualizerAttorney