//Background class implementation. 
//
//

#include "Background.h"

void Background::bgSetup(unsigned int &VAO)
{
	unsigned int VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind VAO
	glBindVertexArray(VAO);
	
	// Bind VBO and buffer the vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(BGverts), BGverts, GL_STATIC_DRAW);
	
	// Bind EBO and buffer the indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(inds), inds, GL_STATIC_DRAW);
		
	// Vertex attribute: position (location = 0 in shader)
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Vertex attribute: color (location = 1 in shader)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind VAO
	glBindVertexArray(0);
}


//Background drawing is now working. 
void Background::renderBG(Shader* shader,unsigned int VAO)
{
	glDisable(GL_DEPTH_TEST);
    	glDepthMask(GL_FALSE);

	if(shader != nullptr)shader -> use();
	else std::cout << "ERROR: SHADER NOT DEFINED" << std::endl;

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, sizeof(inds) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

	glDepthMask(GL_TRUE);
    	glEnable(GL_DEPTH_TEST);
	glBindVertexArray(0);
}
