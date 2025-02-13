#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {

	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		void use();
		~Shader();
		GLuint getID() {return ID;};
		void setMat4(const std::string& variable,const glm::mat4& value);
        void setFloat(const std::string& variable, const glm::float32& value);
        void setVec3(const std::string& variable, const glm::vec3& value);
    private:
		GLuint ID;
        std::string* vPath;
        std::string* fPath;

};


#endif
