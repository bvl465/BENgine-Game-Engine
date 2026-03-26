//Ben La Monica
#pragma once
#ifndef _DrawableAttorney
#define _DrawableAttorney

#include "Drawable.h"

class DrawableAttorney
{
public:
	class GameLoop
	{
	private:
		friend class DrawableManager;

		//Calls Drawable's Draw() function. Called by the DrawableManager each frame in ProcessElements().
		//Parameters:
		//dr - the Drawable to call Draw() on
		static void Draw(Drawable* dr) { dr->Draw(); }

		//Calls Drawable's Draw2D() function. Called by the DrawableManager each frame in ProcessElements() after Draw() is called on all Drawables.
		//Parameters:
		//dr - the Drawable to call Draw2D() on
		static void Draw2D(Drawable* dr) { dr->Draw2D(); }

		//Returns the StorageEntryRef of the Drawable, which is used by the DrawableManager to find and remove the Drawable from its storageList when it is deregistered.
		//Parameters:
		//dr - the Drawable to get the StorageEntryRef of
		static DrawableManager::StorageEntryRef GetStorageEntryRef(Drawable* dr) { return dr->GetStorageEntryRef(); }

		//Sets the StorageEntryRef of the Drawable, which is used by the DrawableManager when it is added to the storageList.
		//Parameters:
		//dr - the Drawable to set the StorageEntryRef of
		//entryRef - the StorageEntryRef to set the Drawable's StorageEntryRef to
		static void SetStorageEntryRef(Drawable* dr, DrawableManager::StorageEntryRef entryRef) { dr->SetStorageEntryRef(entryRef); }
	};

public:
	class Registration
	{
		friend class DrawRegistrationCommand;
		friend class DrawDeregistrationCommand;

	private:
		static void SceneRegistration(Drawable* dr) { dr->SceneRegistration(); }
		static void SceneDeregistration(Drawable* dr) { dr->SceneDeregistration(); }
	};
};
#endif _DrawableAttorney