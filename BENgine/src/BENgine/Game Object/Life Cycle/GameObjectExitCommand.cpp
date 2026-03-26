#include "GameObjectExitCommand.h"
#include "GameObjectAttorney.h"

GameObjectExitCommand::GameObjectExitCommand(GameObject* go) : gameObject(go)
{
}

void GameObjectExitCommand::Execute()
{
	GameObjectAttorney::Registration::DisconnectFromScene(gameObject);

}
