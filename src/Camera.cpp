//  ***CAMERA_CPP***
//
//  (C) Hannah, 2024
//
//  This here is the camera 
//  class what it does is just
//  abstract away all of our problems.
//  Now we dont have any problems (except for putting it all together)
//
//  anyways this is a working part that i dont think ill need to 
//  actually change much at all. 
//
//  Not that that doesnt mean i cant add more stuff to it, 
//  Like i could totally have look modes for 
//  Target/gimbal(if thats the right word)
//  
//  But again, that can be done way later.

#include "Camera.h"

//Pretty simple initializer, nothing to serious.
//(Get the templightPos OUT of this class. NOW!)
Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up)
{
	this -> position = position;
	this -> target = target;
	this -> up = up;
    this -> TempLightPos = glm::vec3(0.0, 3.0, 0.0);
}

//Get the view matrix, actually i dont even know
//if i have EVER used this thing. 
//but it looks pretty so we can keep it!
glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt( position , target , up );
}

//This here is actually really really important. 
//This here is going to take our mess of a 3D scene 
//and transform it into a glorious 2D image 
//That may be blessed upon our sight!
glm::mat4 Camera::getProjectionMatrix(float fov, float aspect, float near, float far)
{
	return glm::perspective(fov, aspect, near, far);
}

//Then we pull out the position.
glm::vec3 Camera::getPosition()
{
	return position;
}

//And believe it or not we can actually just 
//set the camera target. yay.
void Camera::setTarget(glm::vec3 targ)
{
	this -> target = targ;
}
