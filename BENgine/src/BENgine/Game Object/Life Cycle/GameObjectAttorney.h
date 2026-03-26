//Ben La Monica
#pragma once
#ifndef _GameObjectAttorney
#define _GameObjectAttorney

#include "../GameObject.h"

class GameObjectAttorney
{
public:
	class Registration
	{
		friend class GameObjectEntryCommand;
		friend class GameObjectExitCommand;

	private:
		static void DisconnectFromScene(GameObject* go) { go->DisconnectFromScene(); }
		static void ConnectToScene(GameObject* go) { go->ConnectToScene(); }
	};
};
#endif _GameObjectAttorney