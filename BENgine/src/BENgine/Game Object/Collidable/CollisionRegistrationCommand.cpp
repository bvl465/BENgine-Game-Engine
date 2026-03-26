#include "CollisionRegistrationCommand.h"
#include "CollidableAttorney.h"

CollisionRegistrationCommand::CollisionRegistrationCommand(Collidable* co) : collidable(co)
{

}

void CollisionRegistrationCommand::Execute()
{
	CollidableAttorney::Registration::SceneRegistration(collidable);
}
