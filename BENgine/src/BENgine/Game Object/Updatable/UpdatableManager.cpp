#include "UpdatableManager.h"
//#include "Updatable.h"
#include "UpdatableAttorney.h"
void UpdatableManager::ProcessElements()
{
	for (StorageList::iterator it = storageList.begin(); it != storageList.end(); it++) {
		UpdatableAttorney::GameLoop::Update(*it);
	}
}

void UpdatableManager::Register(Updatable* up)
{
	UpdatableAttorney::GameLoop::SetStorageEntryRef(up, storageList.insert(storageList.end(), up));
}

void UpdatableManager::Deregister(Updatable* up)
{
	storageList.erase(UpdatableAttorney::GameLoop::GetStorageEntryRef(up));
}
