// Background class - it's mostly here just so i can get it out of my main.
//
#include <array>
#include "Shader.h"


class Background{
	//Background vertices for rendering.

    std::array<float, 20> BGverts;
    std::array<GLuint, 6> inds;

	public:
		void bgSetup(unsigned int &VAO);
		void renderBG(Shader* shader, unsigned int VAO);
		Background();
};


/*
 *
//Right here is the background data.
//First two floats are The position,
//Color data is the third, fourth fifth.
//Each line is a new vertex.
//All this does is make a rectangle on the screen.
GLfloat verts[] = 
{
		-1.0f, 1.0f,  0.90f, 0.90f, 0.995f,
		-1.0f, -1.0f, 0.5f, 0.5f, 0.750f,
		1.0f, -1.0f,  0.25f, 0.25f, 0.90f, 
		1.0f, 1.0f,   0.90f, 0.90f, 0.995f
};

//This is the indices essentailly it draws in this order.
GLuint inds[] = 
{
		0, 1, 2,
		0, 2, 3	
};
*/
