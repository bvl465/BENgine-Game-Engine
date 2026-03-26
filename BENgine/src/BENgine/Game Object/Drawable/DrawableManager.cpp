#include "DrawableManager.h"
#include "Drawable.h"
#include "DrawableAttorney.h"
void DrawableManager::ProcessElements()
{
	for (StorageList::iterator it = storageList.begin(); it != storageList.end(); it++) {
		DrawableAttorney::GameLoop::Draw(*it);
	}
	for (StorageList::iterator it = storageList.begin(); it != storageList.end(); it++) {
		DrawableAttorney::GameLoop::Draw2D(*it);
	}
	//Note:
	//While going through the same list twice may seem bad, having a separate lists
	//for Draw() and Draw2D() would mean that a drawable could appear in
	//both lists and also that each Drawable would need 2 storageEntryRefs.
}

void DrawableManager::Register(Drawable* dr)
{
	DrawableAttorney::GameLoop::SetStorageEntryRef(dr, storageList.insert(storageList.end(), dr));
}

void DrawableManager::Deregister(Drawable* dr)
{
	storageList.erase(DrawableAttorney::GameLoop::GetStorageEntryRef(dr));
}
