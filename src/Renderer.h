#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Window.h"

class Renderer {

		Window* ghge_window;
		Shader* shader;
<<<<<<< HEAD
		
		void (*backgroundDraw)();
	
=======
        	GLuint winWidth, winHeight;
>>>>>>> main
	public:
		Renderer(const GLuint &winWidth, const GLuint &winHeight);
		void render(Mesh& mesh, Camera& camera);
		void cleanup();
		void swapwindow();
		void setShader(Shader *shader_);
<<<<<<< HEAD
		
		void setBGdrawMethod(void (*ptr)());
=======
		SDL_Window* getWindow(){ return window;};		
>>>>>>> main
};

#endif
