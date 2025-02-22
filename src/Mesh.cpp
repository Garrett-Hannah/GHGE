#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
{
	this -> vertices = vertices;
	this -> indices = indices;
	this -> textures = textures;

    //modelScale = glm::mat4(1);
    //modelRotation = glm::mat4(1);
	modelScale = glm::vec3(1.0f);
	modelPosition = glm::vec3(0.0f);
	modelRotation = glm::vec3(0.0f);

	

	//calculateNormals();
	setupMesh();
}

void Mesh::calculateNormals()
{
	for(size_t i = 0; i < indices.size(); i+=3)
	{
		Vertex v0, v1, v2;
		v0 = vertices[indices[i]];
		v1 = vertices[indices[i+1]];
		v2 = vertices[indices[i+2]];

		
		glm::vec3 Normal = -glm::normalize(glm::cross((v2.Position - v0.Position), (v1.Position - v0.Position)));


		//vertices[i].Normal = Normal;
		//vertices[i].Normal = Normal;
		//vertices[i].Normal = Normal;

		


		vertices[indices[i]].Normal = glm::normalize(v0.Normal + Normal);
		vertices[indices[i+1]].Normal = glm::normalize(v1.Normal + Normal);
		vertices[indices[i+2]].Normal = glm::normalize(v2.Normal + Normal);
	}
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);

    std::cout << glGetError() << std::endl;
}

void Mesh::Draw(Shader &shader)
{
	shader.use();
	
	

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);


}
