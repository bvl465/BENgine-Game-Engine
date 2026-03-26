//Ben La Monica
#pragma once
#ifndef _UpdatableManager
#define _UpdatableManager
#include <list>
class Updatable;
class UpdatableManager
{
private:
	using StorageList = std::list<Updatable*>;

	//The list of Updatables to call Update() on through the UpdatableAttorney
	StorageList storageList;
public:
	UpdatableManager() = default;
	UpdatableManager(const UpdatableManager&) = delete;
	UpdatableManager& operator=(const UpdatableManager&) = delete;
	~UpdatableManager() = default;

	//Calls Update() on all Updatables in the storageList via UpdatableAttorney.
	void ProcessElements();

	//Adds the passed Updatable to the storageList.
	//Parameters:
	//up - the Updatable to register
	void Register(Updatable* up);

	//Removes the passed Updatable from the storageList.
	//Parameters:
	//up - the Updatable to deregister.
	void Deregister(Updatable* up);

	using StorageEntryRef = StorageList::iterator;

};
#endif _UpdatableManager