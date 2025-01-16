#include "Window.h"

Window::Window ( const GLuint &winW, const GLuint &winH )
{
	winWidth = winW;
	winHeight = winH;

	std::cout << "Window Dimensions Set. " 
		  << winW << " x " << winH << std::endl;
}

//Initializes a window through SDL2. 
//This also sets the Opengl window.
GLint Window::initWindow()
{
    // Step 1: Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Step 2: Set OpenGL version and profile (e.g., OpenGL 3.3 Core)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Step 3: Create an SDL window with OpenGL support
    sdl_window = SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_OPENGL);
    if (!sdl_window) {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -2;
    } 

    // Step 4: Create an OpenGL context associated with the SDL window
    gl_context = SDL_GL_CreateContext(sdl_window);
    if (!gl_context) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(sdl_window);
        SDL_Quit();
        return -3;
    }

    return 1;
}

void Window::cleanup()
{	
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(sdl_window);
}
