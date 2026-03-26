//Ben La Monica
#pragma once
#ifndef _BENgineAttorney
#define _BENgineAttorney

#include "BENgine.h"

class BENgineAttorney
{
public:
	class Freeze
	{
	private:
		friend class FreezeTime;
		static float GetTime() { return BENgine::GetTime(); }
	};
};
#endif _BENgineAttorney