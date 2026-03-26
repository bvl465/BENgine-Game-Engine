#include "GameObjectEntryCommand.h"
#include "GameObjectAttorney.h"

GameObjectEntryCommand::GameObjectEntryCommand(GameObject* go) : gameObject(go)
{
}

void GameObjectEntryCommand::Execute()
{
	GameObjectAttorney::Registration::ConnectToScene(gameObject);

}
