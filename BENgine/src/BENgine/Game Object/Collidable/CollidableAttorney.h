//Ben La Monica
#pragma once
#ifndef _CollidableAttorney
#define _CollidableAttorney

#include "Collidable.h"

class CollidableAttorney
{
public:
	class GameLoop
	{
	private:
		friend class CollidableGroup;
		static CollidableGroup::StorageEntryRef GetStorageEntryRef(Collidable* co) { return co->GetStorageEntryRef(); }
		static void SetStorageEntryRef(Collidable* co, CollidableGroup::StorageEntryRef entryRef) { co->SetStorageEntryRef(entryRef); }
	};

public:
	class Registration
	{
		friend class CollisionRegistrationCommand;
		friend class CollisionDeregistrationCommand;

	private:
		static void SceneRegistration(Collidable* co) { co->SceneRegistration(); }
		static void SceneDeregistration(Collidable* co) { co->SceneDeregistration(); }
	};
};
#endif _CollidableAttorney