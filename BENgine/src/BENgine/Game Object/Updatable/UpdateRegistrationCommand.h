//Ben La Monica
#pragma once
#ifndef _UpdateRegistrationCommand
#define _UpdateRegistrationCommand
#include "../../Patterns/CommandBase.h"
#include "Updatable.h"
class Updatable;
class UpdateRegistrationCommand : public CommandBase
{
public:
	UpdateRegistrationCommand() = delete;
	UpdateRegistrationCommand(const UpdateRegistrationCommand&) = delete;
	UpdateRegistrationCommand& operator=(const UpdateRegistrationCommand&) = delete;
	~UpdateRegistrationCommand() = default;


	UpdateRegistrationCommand(Updatable* up);

	//Adds the Updatable to the UpdatableManager's storageList so it will be updated each frame.
	virtual void Execute() override;

	
private:
	Updatable* updatable;
};
#endif _UpdateRegistrationCommand