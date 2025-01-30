//Writing the implementation of shader class?
#include "Shader.h"

Shader::Shader(const std::string &vertexPath, const std::string& fragmentPath)
{
	std::cout << vertexPath << std::endl;
	std::cout <<fragmentPath << std::endl;


    std::string vertexCode;
	std::string fragmentCode;



	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions( std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions( std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();


		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(std::ifstream::failure &e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;

	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();


	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION::FAILED\n" << infoLog << std::endl;
	};



	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION::FAILED\n" << infoLog << std::endl;
	};

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}


	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

//This will use the shader via its ID. 
void Shader::use()
{
	glUseProgram(ID);
    GLenum error = glGetError();
    if(error != GL_NO_ERROR) {
        //std::cerr << "Error after glUseProgram: " << error << std::endl;
    }
}


void Shader::setMat4(const std::string &variable,const glm::mat4 &matrix)
{
	// Retrieve the location of the uniform variable in the shader
        int location = glGetUniformLocation(ID, variable.c_str());

        // Set the uniform value
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}


void Shader::setFloat(const std::string &variable,const GLfloat &value)
{
	// Retrieve the location of the uniform variable in the shader
        int location = glGetUniformLocation(ID, variable.c_str());

        // Set the uniform value
        glUniform1f(location, value);
}

Shader::~Shader() {
    glDeleteProgram(ID);
}

