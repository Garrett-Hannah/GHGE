#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up)
{
	this -> position = position;
	this -> target = target;
	this -> up = up;
    this -> TempLightPos = glm::vec3(0.0, 3.0, 0.0);
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt( position , target , up );
}

glm::mat4 Camera::getProjectionMatrix(float fov, float aspect, float near, float far)
{
	return glm::perspective(fov, aspect, near, far);
}

glm::vec3 Camera::getPosition()
{
	return position;
}

void Camera::setTarget(glm::vec3 targ)
{
	this -> target = targ;
}
