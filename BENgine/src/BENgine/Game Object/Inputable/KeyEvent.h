//Ben La Monica
#pragma once
#ifndef _KeyEvent
#define _KeyEvent

//States a key can be in
enum class KeyEvent
{
	//The key was pressed this frame
	KEY_PRESSED,

	//The key was released this frame
	KEY_RELEASED,

	//The key was pressed in a previous frame and is still being held down
	KEY_DOWN,

	//The key was released in a previous frame and is still up
	KEY_UP
};
#endif _KeyEvent