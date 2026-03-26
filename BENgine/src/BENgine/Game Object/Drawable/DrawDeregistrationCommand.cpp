#include "DrawDeregistrationCommand.h"
#include "DrawableAttorney.h"

DrawDeregistrationCommand::DrawDeregistrationCommand(Drawable* dr) : drawable(dr)
{
}

void DrawDeregistrationCommand::Execute()
{
	DrawableAttorney::Registration::SceneDeregistration(drawable);

}
