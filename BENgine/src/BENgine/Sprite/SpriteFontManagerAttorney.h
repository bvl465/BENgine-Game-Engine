//Ben La Monica
#pragma once
#ifndef _SpriteFontManagerAttorney
#define _SpriteFontManagerAttorney

#include "SpriteFontManager.h" 

class SpriteFontManagerAttorney
{

	friend class BENgine;

private:
	//Only BENgine can call the delete method for the SpriteFontManager
	static void Delete() { SpriteFontManager::Delete(); }

};
#endif _SpriteFontManagerAttorney
