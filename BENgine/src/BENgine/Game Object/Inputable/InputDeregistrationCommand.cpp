#include "InputDeregistrationCommand.h"
#include "InputableAttorney.h"



InputDeregistrationCommand::InputDeregistrationCommand(Inputable* in, AZUL_KEY k, KeyEvent ke) : inputable(in), key(k), keyEvent(ke)
{
}

void InputDeregistrationCommand::Execute()
{
	InputableAttorney::Registration::SceneDeregistration(inputable, key, keyEvent);
}