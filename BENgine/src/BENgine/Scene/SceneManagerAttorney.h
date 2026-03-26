//Ben La Monica
#pragma once
#ifndef _SceneManagerAttorney
#define _SceneManagerAttorney
#include "AzulCore.h"

#include "SceneManager.h"
class SceneManagerAttorney
{
public:
	class GameLoop
	{
		friend class BENgine;

	private:
		static void Update() { SceneManager::Update(); }
		static void Draw() { SceneManager::Draw(); }
		static void Delete() { SceneManager::Delete(); }
	};
	class SceneStrategy
	{
		friend class SceneChangeStrategy;

	private:
		static void ChangeScene(Scene* scene) { SceneManager::ChangeScene(scene); }
	};
};
#endif _SceneManagerAttorney