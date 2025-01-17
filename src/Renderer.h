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
		
		void (*backgroundDraw)();
	    

        	GLuint winWidth, winHeight;
	public:
		Renderer(const GLuint &winWidth, const GLuint &winHeight);
		void render(Mesh& mesh, Camera& camera);
		void cleanup();
		void swapwindow();
		void setShader(Shader *shader_);
	    void init();

		void setBGdrawMethod(void (*ptr)());
		SDL_Window* getWindow(){ return ghge_window -> getSdlWindow();};		
};

#endif
