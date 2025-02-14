/* 
 *   ***GAMEOBJECT CLASS***
 *
 *   This class is going to be important because of how its going to handle 
 *   the loop updates from each frame.
 *
 *   i imagine that all, and I mean ALL game objects are going to 
 *   have some very very basic functionality. 
 *   
 *   I will bundle the gameObject component with other things. i dont really like that
 *   this is all going to be individually implemented, but oh well.
 *
 *
 */

#include <SDL2/SDL.h>
#include <cstdint>
#include <sys/types.h>

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H 

class gameObject 
{
    private:
        //This means we are allowing for 2^8 
        //Game objects, which is quite a bit to begin.
        //Of course this could change...
        uint8_t id;

    public:
        //each one will have an upward refernce to the engine.
        //GHGEngine* engine;

        //Constructors/destructors.
        gameObject(uint8_t ID) : id(ID) {};
        ~gameObject();

        //Process
        void processUpdate(float dt);

         




};

#endif
