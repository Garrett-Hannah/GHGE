/* INPUTMANAGER CLASS..
 *
 * This class is dedicated to processing
 *
 *
 *
 * KNOWN ISSUE: KEYBOARD ROLLOVER.
 * on the surface pro 9, the rollover 
 * makes it so that when you 
 * press WASD AND O/P.
 * It will not accurately send data.
 *
 * Unfourtnately this is indeed a hardware limitation.
 * So there isnt really a fix.
 */


#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL.h>
#include <iostream>

#include "inputDefinitions.h"

//the input class is going to be saving up inputs,
//Keeping track of them each frame.


class InputManager
{
	public:
        static InputManager* getInstance();

        /// Updates Manager State
        void update(float cameraX=0, float cameraY = 0);

        /// Tells if 'key' was just pressed
        bool isKeyDown(int key);
        
        /// Tells if 'key' was just released
        bool isKeyUp(int key);

        /// Helpers for returning if cetrain buttons pressed.
        ///
        bool shift();

        bool ctrl();

        bool alt();

        bool isMouseDown(MouseButton button);

        bool isMouseUp(MouseButton button);

        bool isKeyPressed(KeyboardKey key);

        bool isMousePressed(MouseButton button);

        bool quitRequested();

        int getMouseX();

        int getMouseY();

        void lock();

        void unlock();

        bool isMouseInside();

        static bool isPrintable(SDL_Keycode key);

        bool isPrintableKeyDown();
        std::string getCurPrintableKey();


        InputManager();

        InputManager(InputManager const&) {};
        void operator=(InputManager const&) {};
        
        //pointer to size of array? doesnt seem to work though.
        int* numKeys;
    
    private:

        static InputManager* instance;


        const uint8_t* keyboard;

        uint8_t mouse;

        int mouseX;

        int mouseY;

        bool keyDown[KEYBOARD_SIZE];

        bool keyUp[KEYBOARD_SIZE];
        
        bool mouseDown[MOUSE_MAX];
        bool mouseUp[MOUSE_MAX];

        bool quit_queued;

        int curPrintableKey;

        bool isLocked;
};

#endif
