//Ben La Monica
#pragma once
#ifndef _ImageManagerAttorney
#define _ImageManagerAttorney

#include "ImageManager.h" 

class ImageManagerAttorney
{

	friend class BENgine;

private:
	//Only BENgine can call the delete method for the ImageManager
	static void Delete() { ImageManager::Delete(); }

};
#endif _ImageManagerAttorney