//Ben La Monica
#pragma once
#ifndef _DrawRegistrationCommand
#define _DrawRegistrationCommand
#include "../../Patterns/CommandBase.h"
#include "Drawable.h"
class Drawable;
class DrawRegistrationCommand : public CommandBase
{
public:
	DrawRegistrationCommand() = delete;
	DrawRegistrationCommand(const DrawRegistrationCommand&) = delete;
	DrawRegistrationCommand& operator=(const DrawRegistrationCommand&) = delete;
	~DrawRegistrationCommand() = default;


	DrawRegistrationCommand(Drawable* dr);

	//Adds the Drawable to the DrawableManager's storageList to be drawn each frame.
	virtual void Execute() override;

	
private:
	Drawable* drawable;
};
#endif _DrawRegistrationCommand