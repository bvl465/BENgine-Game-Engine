//Ben La Monica
#pragma once
#ifndef _DrawableManager
#define _DrawableManager
#include <list>
class Drawable;
class DrawableManager
{
private:
	using StorageList = std::list<Drawable*>;

	//The list of Drawables to call Draw() and Draw2D() on.
	StorageList storageList;
public:
	DrawableManager() = default;
	DrawableManager(const DrawableManager&) = delete;
	DrawableManager& operator=(const DrawableManager&) = delete;
	~DrawableManager() = default;

	//Calls Draw() and Draw2D() on all registered Drawables in the storageList.
	void ProcessElements();


	//Adds the passed Drawable to the storageList.
	//Parameters:
	//dr - the Drawable to register
	void Register(Drawable* dr);

	//Removes the passed Drawable from the storageList.
	//Parameters:
	//dr - the Drawable to deregister
	void Deregister(Drawable* dr);

	using StorageEntryRef = StorageList::iterator;


};
#endif _DrawableManager