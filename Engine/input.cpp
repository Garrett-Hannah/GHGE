#include "input.h"


Input::Input()
{
}


void Input::updateKeys(SDL_Event* event)
{
	if(event -> type != SDL_KEYDOWN && event -> type != SDL_KEYUP)
	{

		justPressedKeys[event -> key.keysym.scancode] = false;
		justReleasedKeys[event -> key.keysym.scancode] = false;
	}
	if( event -> type == SDL_KEYDOWN ) 
	{ 
		keys[event -> key.keysym.scancode] = true;
		justPressedKeys[event -> key.keysym.scancode] = true;
	}
	else if( event -> type == SDL_KEYUP)
	{
		keys[event -> key.keysym.scancode] = false;
		justReleasedKeys[event -> key.keysym.scancode] = true;
	}
}

bool Input::isKeyPressed(SDL_Scancode code)
{
	return keys[code];
}


bool Input::isKeyJustPressed(SDL_Scancode code)
{
	return justPressedKeys[code];
}


bool Input::isKeyJustReleased(SDL_Scancode code)
{
	return justReleasedKeys[code];
}

void Input::resetKeyPresses()
{
	for(Uint32 i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		justReleasedKeys[i] = false;
		justPressedKeys[i] = false;
	}
}
