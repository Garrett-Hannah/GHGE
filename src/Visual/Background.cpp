//Background class implementation. 
//
//

#include "Background.h"


Background::Background()
{
    BGverts = {-1.0f, 1.0f,  0.90f, 0.90f, 0.950f,
        -1.0f, -1.0f, 0.5f, 0.5f, 0.750f,
        1.0f, -1.0f,  0.5f, 0.5f, 0.750f, 
        1.0f, 1.0f,   0.90f, 0.90f, 0.950f};




    inds = {0, 1, 2, 0, 2, 3};
}

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(BGverts), BGverts.data(), GL_STATIC_DRAW);
	
	// Bind EBO and buffer the indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(inds), inds.data(), GL_STATIC_DRAW);
		
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

	if(shader != nullptr)
    {
        
	    glDisable(GL_DEPTH_TEST);
    	glDepthMask(GL_FALSE);

        shader -> use();

        
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, sizeof(inds) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

        glDepthMask(GL_TRUE);
            glEnable(GL_DEPTH_TEST);
        glBindVertexArray(0);
    }
	else 
    {
        std::cout << "ERROR: SHADER NOT DEFINED" << std::endl;
        

        
    }
    
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cout << "OpenGL Error: 0x" << std::hex << err << std::dec << std::endl;
    }
}

