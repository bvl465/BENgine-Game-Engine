//Ben La Monica
#pragma once
#ifndef _InputDeregistrationCommand
#define _InputDeregistrationCommand
#include "../../Patterns/CommandBase.h"
#include "KeyEvent.h"
#include "AzulCore.h"
#include "Inputable.h"
class Inputable;
class InputDeregistrationCommand : public CommandBase
{
public:
	InputDeregistrationCommand() = delete;
	InputDeregistrationCommand(const InputDeregistrationCommand&) = delete;
	InputDeregistrationCommand& operator=(const InputDeregistrationCommand&) = delete;
	~InputDeregistrationCommand() = default;


	InputDeregistrationCommand(Inputable* in, AZUL_KEY k, KeyEvent ke);

	virtual void Execute() override;



private:
	Inputable* inputable;
	//NOT CONST BECAUSE I MAY USE RECYCLING OF THESE IN THE FUTURE
	AZUL_KEY key;
	KeyEvent keyEvent;

};
#endif _InputDeregistrationCommand