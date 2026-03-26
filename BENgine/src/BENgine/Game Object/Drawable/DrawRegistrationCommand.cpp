#include "DrawRegistrationCommand.h"
#include "DrawableAttorney.h"

DrawRegistrationCommand::DrawRegistrationCommand(Drawable* dr) : drawable(dr)
{
}

void DrawRegistrationCommand::Execute()
{
	DrawableAttorney::Registration::SceneRegistration(drawable);
}
