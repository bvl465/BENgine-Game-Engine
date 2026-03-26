
#include "BENgine.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{          
	// Create game 
	BENgine::BENgineRun();

	// Game clean up
	BENgine::BENgineDestroy();
	return 0;                                       
}

