#include "inputManager.h"

InputManager* InputManager::instance = nullptr;

InputManager::InputManager():
    keyboard(nullptr),
    mouse(0),
    mouseX(0),
    mouseY(0),
    quit_queued(false),
    isLocked(false)
{ };

bool InputManager::isKeyPressed(KeyboardKey key)
{
    if (this -> isLocked ) return false;

    if(!(this -> keyboard ))
        return false;

    int sdl_key = static_cast<int>(key);

    if(this->keyboard[sdl_key])
        return true;

    return false;
};

bool InputManager::isKeyUp(int key)
{
    return this -> keyboard[key];
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
        instance = new InputManager();

    return instance;
}

void InputManager::update(float cameraX, float caeraY)
{
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
}
