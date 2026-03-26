//Ben La Monica
#pragma once
#ifndef _RegistrationState
#define _RegistrationState

//Used to determine the current registration state of X-ables and GameObjects to make sure they don't submit multiple registration or deregistration commands
enum class RegistrationState
{
	//Object is registered to the scene
	CURRENTLY_REGISTERED,

	//Object is not registered to the scene
	CURRENTLY_DEREGISTERED,

	//Object has submitted a registration and will be added to the scene next frame
	PENDING_REGISTRATION,

	//Object has submitted a deregistration and will be removed from the scene next frame
	PENDING_DEREGISTRATION
};
#endif _RegistrationState