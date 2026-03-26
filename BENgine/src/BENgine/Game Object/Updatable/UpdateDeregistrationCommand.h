//Ben La Monica
#pragma once
#ifndef _UpdateDeregistrationCommand
#define _UpdateDeregistrationCommand
#include "../../Patterns/CommandBase.h"
#include "Updatable.h"
class Updatable;
class UpdateDeregistrationCommand : public CommandBase
{
public:
	UpdateDeregistrationCommand() = delete;
	UpdateDeregistrationCommand(const UpdateDeregistrationCommand&) = delete;
	UpdateDeregistrationCommand& operator=(const UpdateDeregistrationCommand&) = delete;
	~UpdateDeregistrationCommand() = default;


	UpdateDeregistrationCommand(Updatable* up);

	//Removes the Updatable from the UpdatableManager's storageList so it will not be updated each frame.
	virtual void Execute() override;

	
private:
	Updatable* updatable;
};
#endif _UpdateDeregistrationCommand