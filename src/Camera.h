#ifndef CAMERA_H
#define CAMERA_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


class Camera{

	public:
		Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up);
		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix(float fov, float aspect, float near, float far);	
		void setPosition(const glm::vec3 pos){ position = pos;};
		glm::vec3 getPosition();
		void setTarget(glm::vec3 targ);
	private:
		glm::vec3 position;
		glm::vec3 target;
		glm::vec3 up;



};


#endif
