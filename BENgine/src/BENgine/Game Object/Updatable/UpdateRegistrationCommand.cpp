#include "UpdateRegistrationCommand.h"
#include "UpdatableAttorney.h"


UpdateRegistrationCommand::UpdateRegistrationCommand(Updatable* up) : updatable(up)
{
}

void UpdateRegistrationCommand::Execute()
{
	UpdatableAttorney::Registration::SceneRegistration(updatable);
}
