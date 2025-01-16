#include <SDL2/SDL.h>

//the input class is going to be saving up inputs,
//Keeping track of them each frame.


class Input
{
	bool keys[SDL_NUM_SCANCODES] = {false};
	bool justPressedKeys[SDL_NUM_SCANCODES] = {false};
	bool justReleasedKeys[SDL_NUM_SCANCODES] = {false};

	public:
		Input();
		void updateKeys(SDL_Event* event);
		bool isKeyPressed(SDL_Scancode code);
		bool isKeyJustPressed(SDL_Scancode code);
		bool isKeyJustReleased(SDL_Scancode code);
		void resetKeyPresses();
};
