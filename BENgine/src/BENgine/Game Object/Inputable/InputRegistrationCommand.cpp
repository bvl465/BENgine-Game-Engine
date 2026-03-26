#include "InputRegistrationCommand.h"
#include "InputableAttorney.h"



InputRegistrationCommand::InputRegistrationCommand(Inputable* in, AZUL_KEY k, KeyEvent ke) : inputable(in), key(k), keyEvent(ke)
{
}

void InputRegistrationCommand::Execute()
{
	InputableAttorney::Registration::SceneRegistration(inputable, key, keyEvent);
}