//Ben La Monica
#pragma once
#ifndef _DrawDeregistrationCommand
#define _DrawDeregistrationCommand
#include "../../Patterns/CommandBase.h"
#include "Drawable.h"
class Drawable;
class DrawDeregistrationCommand : public CommandBase
{
public:
	DrawDeregistrationCommand() = delete;
	DrawDeregistrationCommand(const DrawDeregistrationCommand&) = delete;
	DrawDeregistrationCommand& operator=(const DrawDeregistrationCommand&) = delete;
	~DrawDeregistrationCommand() = default;


	DrawDeregistrationCommand(Drawable* dr);

	//Removes the Drawable from the DrawableManager's storageList so it will not be drawn each frame.
	virtual void Execute() override;

	
private:
	Drawable* drawable;
};
#endif _DrawDeregistrationCommand