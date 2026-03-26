//Ben La Monica
#pragma once
#include <list>
#ifndef _SceneRegistrationBroker
#define _SceneRegistrationBroker
class CommandBase;
class SceneRegistrationBroker
{

public:

	SceneRegistrationBroker() = default;
	SceneRegistrationBroker(const SceneRegistrationBroker&) = delete;
	SceneRegistrationBroker& operator=(const SceneRegistrationBroker&) = delete;
	~SceneRegistrationBroker() = default;

	void AddCommand(CommandBase* cmd);
	void ExecuteCommands();

protected:


private:
	
	using CommandList = std::list<CommandBase*>;
	CommandList commandList;



};
#endif _SceneRegistrationBroker