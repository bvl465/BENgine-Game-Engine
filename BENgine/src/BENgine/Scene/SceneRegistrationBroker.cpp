#include "../Patterns/CommandBase.h"
#include "SceneRegistrationBroker.h"

void SceneRegistrationBroker::AddCommand(CommandBase* cmd)
{
	commandList.push_back(cmd);
}

void SceneRegistrationBroker::ExecuteCommands()
{
	for (CommandList::iterator it = commandList.begin(); it != commandList.end(); it++) {
		(*it)->Execute();
	}
	commandList.clear();
}
