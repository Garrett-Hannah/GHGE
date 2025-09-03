#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <iostream>


//This class is dedicated to creating windows. 

//You will first initialize the window. Declaring width and height. 
//
//Then you will initialize it. I dont know why this isnt immediately in the 
//Constructor function but Oh well. 
class Window
{
	private:
		GLuint winWidth, winHeight;
		SDL_Window* sdl_window;

	public:
		SDL_GLContext gl_context;
	
        //Constructor Method
	//Defines width and height.
		Window ( const GLuint &winW, const GLuint &winH );

		//Initializes the window, returns an integer
		//Based on any errrors. 
		GLint initWindow();

		const GLuint getWinWidth() { return winWidth; };
		const GLuint getWinHeight() { return winHeight; }; 

		void cleanup();

		SDL_Window* getSdlWindow() { return sdl_window; };
};

#endif
