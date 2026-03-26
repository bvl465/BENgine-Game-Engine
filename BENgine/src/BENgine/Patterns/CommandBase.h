//Ben La Monica
#pragma once
#ifndef _CommandBase
#define _CommandBase
class CommandBase
{
public:

	CommandBase() = default;
	CommandBase(const CommandBase&) = delete;
	CommandBase& operator=(const CommandBase&) = delete;
	~CommandBase() = default;

	virtual void Execute() = 0;
};
#endif _CommandBase