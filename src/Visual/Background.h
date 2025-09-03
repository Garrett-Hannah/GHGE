// Background class - it's mostly here just so i can get it out of my main.
//
#include "Shader.h"


class Background{
	//Background vertices for rendering.

	float BGverts[20]; 	//Bg Indices
	GLuint inds[6];


	public:
		void bgSetup(unsigned int &VAO);
		void renderBG(Shader* shader, unsigned int VAO);
		Background(){
			float BGvert[] = {-1.0f, 1.0f,  0.90f, 0.90f, 0.950f,
			-1.0f, -1.0f, 0.5f, 0.5f, 0.750f,
			1.0f, -1.0f,  0.5f, 0.5f, 0.750f, 
			1.0f, 1.0f,   0.90f, 0.90f, 0.950f};



			GLuint ind[] = {0, 1, 2, 0, 2, 3};

			for(int i = 0; i < 6; i++)
			{
				inds[i] = ind[i];
			}

			for(int i = 0; i < 20; i++)
			{
				BGverts[i] = BGvert[i];
			}
		}
};

