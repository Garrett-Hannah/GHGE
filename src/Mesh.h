#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;

};

struct Texture {
	unsigned int id;
	std::string type;
};

class Mesh {
	public:
		std::vector<Vertex> 	vertices;
		std::vector<GLuint>	 	indices;
		std::vector<Texture>	textures;

		glm::vec3 modelPosition;
        	glm::vec3 modelScale;
		glm::vec3 modelRotation;



		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		void Draw(Shader &shader);

		GLuint VAO, VBO, EBO;

		//Take all faces and calculate the normal from each one.
		void calculateNormals();

		void setupMesh();
	private:
		
};

#endif
