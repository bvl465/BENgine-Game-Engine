#include "UpdateDeregistrationCommand.h"
#include "UpdatableAttorney.h"

UpdateDeregistrationCommand::UpdateDeregistrationCommand(Updatable* up) : updatable(up)
{
}

void UpdateDeregistrationCommand::Execute()
{
	UpdatableAttorney::Registration::SceneDeregistration(updatable);
}
