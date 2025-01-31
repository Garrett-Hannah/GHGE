/* (C) Garrett Hannah, 2024
 * Collsion Object Header file
 * 
 * *What does this class do/handle*
 *
 * first of all, this class will be handling
 * Positions. 
 *
 * For the time being, I will be doing *only* 
 * a 3d box for collisions, and it will be limited
 * to only the updown/leftright directions (so fairly limited.)
 *
 * So in order to decide collision, only
 * two positions will need to be known. 
 *
 * This of course being the topleft 
 * and bottom left.
 * 
 * Maybe to make visualization, I will include a drawBound
 * Function.
 *
 */

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

class collisionObject
{
    private:
    //* This should eventually be replaced with a 
    //primitive shape object i think
    glm::vec3 topLeft;
    glm::vec3 bottomRight;



    public:
        glm::vec3 getTL();
        glm::vec3 getBR();
    
        //This means that opengl will be a required include. 
        void drawBounds();

        //Returns if the objects are within eachothers bounds. 
        bool isOverlapping(const collisionObject &other);

        
};





#endif
