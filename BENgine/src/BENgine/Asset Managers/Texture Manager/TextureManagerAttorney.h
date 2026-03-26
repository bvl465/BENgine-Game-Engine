//Ben La Monica
#pragma once
#ifndef _TextureManagerAttorney
#define _TextureManagerAttorney

#include "TextureManager.h"

class TextureManagerAttorney
{

	friend class BENgine;

private:
	//Only BENgine can call the delete method for the TextureManager
	static void Delete() { TextureManager::Delete(); }

};
#endif _TextureManagerAttorney