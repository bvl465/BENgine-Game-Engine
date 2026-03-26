//Ben La Monica
#pragma once
#ifndef _ModelManagerAttorney
#define _ModelManagerAttorney

#include "ModelManager.h" 

class ModelManagerAttorney
{

	friend class BENgine;

private:
	//Only BENgine can call the delete method for the ModelManager
	static void Delete() { ModelManager::Delete(); }

};
#endif _ModelManagerAttorney