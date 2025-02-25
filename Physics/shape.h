/*
 *  Shape.h class: 
 *
 *  What is the shape class. its just a shorthand for a few things. 
 *
 *
 *
 *
 *
 * */

#include <glm/vec3.hpp>
#include <GL/gl.h>
#include <iostream>

#ifndef SHAPE_H
#define SHAPE_H 

namespace GHGE
{
    struct cube
    {
        glm::vec3 position;
        float height;
        float width;
        float length;
    };

    struct sphere
    {
        glm::vec3 position;
        float radius;
    };

    struct capsule
    {
        glm::vec3 position;
        float cylinderL;
        float radius;
    };


    //bool collide(const cube& c, const sphere& s)
    //{

    //}
    
    bool collide(const cube& c, const sphere& s);

    bool collide(const sphere& s1, const sphere& s2);
    void drawCube(const cube& c);    
}

#endif
