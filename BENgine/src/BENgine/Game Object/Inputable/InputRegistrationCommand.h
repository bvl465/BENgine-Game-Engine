//Ben La Monica
#pragma once
#ifndef _InputRegistrationCommand
#define _InputRegistrationCommand
#include "../../Patterns/CommandBase.h"
#include "KeyEvent.h"
#include "AzulCore.h"
#include "Inputable.h"
class Inputable;
class InputRegistrationCommand : public CommandBase
{
public:
	InputRegistrationCommand() = delete;
	InputRegistrationCommand(const InputRegistrationCommand&) = delete;
	InputRegistrationCommand& operator=(const InputRegistrationCommand&) = delete;
	~InputRegistrationCommand() = default;


	InputRegistrationCommand(Inputable* in, AZUL_KEY k, KeyEvent ke);

	virtual void Execute() override;

	

private:
	Inputable* inputable;
	//NOT CONST BECAUSE I MAY USE RECYCLING OF THESE IN THE FUTURE
	AZUL_KEY key;
	KeyEvent keyEvent;

};
#endif _InputRegistrationCommand