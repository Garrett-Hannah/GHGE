#include "inputManager.h"

#include <cstdint>

InputManager* InputManager::instance = nullptr;

InputManager::InputManager(SDL_Window* win):
    keyboard(nullptr),
    mouse(0),
    mouseX(0),
    mouseY(0),
    quit_queued(false),
    isLocked(false)
{
    sdl_window = win;

};

bool InputManager::isKeyPressed(KeyboardKey key)
{
    if ( this -> isLocked ) return false;

    if(!(this -> keyboard ))
        return false;

    uint8_t sdl_key = static_cast<int>(key);
    
    if(this->keyboard[sdl_key])
        return true;

    return false;
};

bool InputManager::isKeyUp(int key)
{
    return this -> keyUp[key];
};

bool InputManager::isKeyDown(int key)
{
    return this -> keyDown[key];
}

bool InputManager::shift()
{
    return keyDown[KEY_LEFT_SHIFT];
}

bool InputManager::quitRequested()
{
    return quit_queued;
}

InputManager* InputManager::getInstance()
{
    if (!instance)
        instance = new InputManager(nullptr);

    return instance;
}

void InputManager::update(float cameraX, float caeraY)
{
    if(isMouseInside())
    {
        prevMouseX = mouseX; prevMouseY = mouseY;

        SDL_GetMouseState(&mouseX, &mouseY);
    }

    int i;
    for(i = 0; i < KEYBOARD_SIZE; i++)
    {
        this -> keyDown[i] = false;
        this -> keyUp[i] = false;
    }

    for ( i = 0; i < MOUSE_MAX; i++)
    {
        this -> mouseDown[i] = false;
        this -> mouseUp[i] = false;
    }
    curPrintableKey = 0;

    SDL_Event event;

    bool keyPressFlag = false;


    while(SDL_PollEvent(&event))
    {
        switch ( event.type )
        {
            case SDL_QUIT:
                this -> quit_queued = true;
                break;

            case SDL_TEXTINPUT:
                break;

            case SDL_KEYDOWN:
            { 
                this -> keyboard = SDL_GetKeyboardState(nullptr);
                
                int index = event.key.keysym.scancode;

                this -> keyDown[index] = true;
            }
        }
    }

    if(this -> isKeyDown(KEY_ESCAPE))
    {
        this -> quit_queued = true;
    }
}

int InputManager::getMouseX()
{
    return mouseX;
}

int InputManager::getMouseY()
{
    return mouseY;
}

bool InputManager::isMouseInside()
{
    if (sdl_window == nullptr) 
        return false;

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    int windowX, windowY, windowWidth, windowHeight;
    SDL_GetWindowPosition(sdl_window, &windowX, &windowY);
    SDL_GetWindowSize(sdl_window, &windowWidth, &windowHeight);


    bool state =  mouseX >= 0 && mouseX < windowWidth &&
           mouseY >= 0 && mouseY < windowHeight;

    return state;
}

int InputManager::getMouseVelX()
{
    return mouseX - prevMouseX;
}

int InputManager::getMouseVelY()
{
    return mouseY - prevMouseY;
}
