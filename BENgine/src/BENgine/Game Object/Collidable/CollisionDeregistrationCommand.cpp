#include "CollisionDeregistrationCommand.h"
#include "CollidableAttorney.h"

CollisionDeregistrationCommand::CollisionDeregistrationCommand(Collidable* co) : collidable(co)
{

}

void CollisionDeregistrationCommand::Execute()
{
	CollidableAttorney::Registration::SceneDeregistration(collidable);
}
