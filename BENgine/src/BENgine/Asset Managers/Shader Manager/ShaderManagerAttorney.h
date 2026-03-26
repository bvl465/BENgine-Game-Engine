//Ben La Monica
#pragma once
#ifndef _ShaderManagerAttorney
#define _ShaderManagerAttorney

#include "ShaderManager.h"

class ShaderManagerAttorney
{

	friend class BENgine;

private:
	//Only BENgine can call the delete method for the ShaderManager
	static void Delete() { ShaderManager::Delete(); }

};
#endif _ShaderManagerAttorney