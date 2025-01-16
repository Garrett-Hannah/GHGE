#include "Renderer.h"
#include <SDL2/SDL_video.h>

//The render funciton. Takes a mesh,
//A camera, and uses the camera transforms
//to draw the mesh in 3D space.
void Renderer::render(Mesh& mesh, Camera& camera)
{
<<<<<<< HEAD
=======
	//Get the view matrix, projection matrix.
>>>>>>> main
	glm::mat4 view = camera.getViewMatrix();
	glm::mat4 projection = camera.getProjectionMatrix(glm::radians(80.0f), (float)winWidth/winHeight, 0.1f, 500.0f);

<<<<<<< HEAD
	GLint winWidth, winHeight;

	winWidth = ghge_window -> getWinWidth();
	winHeight = ghge_window -> getWinHeight();

	glm::mat4 projection = camera.getProjectionMatrix(glm::radians(80.0f), (float)winWidth/winHeight, 0.1f, 100.0f);
=======
>>>>>>> main

	//Apply model transforms.
	glm::mat4 model = glm::translate(glm::mat4(1.0f), mesh.modelPosition);
	model = glm::scale(model, mesh.modelScale);

	//Use the shader attached to this renderer.
	shader -> use();
	shader -> setMat4("projection", projection);
	shader -> setMat4("view", view);
	shader -> setMat4("model", model);

	//Draw the mesh with the shader.
	mesh.Draw(*shader);

	//Attempt to see if any errors had occured.
	GLenum error = glGetError();
	if(error != GL_NO_ERROR) {
		std::cout << "Opengl Error: " << error << std::endl;
	}
}

<<<<<<< HEAD

Renderer::Renderer(const GLuint &winWidth_,const GLuint &winHeight_)
=======
//Simply initiailze the window width/height.
Renderer::Renderer(GLuint winWidth_, GLuint winHeight_)
>>>>>>> main
{
    ghge_window = new Window(winWidth_, winHeight_);

    ghge_window -> initWindow();

    if( ghge_window == nullptr ) 
    {
	    std::cerr << "(Renderer::Renderer) Err: failed to init ghge window!" << std::endl;
    }


    GLenum glewStatus = glewInit();

    if( glewStatus != GLEW_OK )
    {
	    std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(glewStatus ) << std::endl;
	    SDL_GL_DeleteContext( ghge_window -> gl_context );
	    SDL_DestroyWindow( ghge_window -> getSdlWindow() );
    }

    std::cout << "Renderer Succesfully initialized" << std::endl;



}

//Cleanup some of the SDL components, like the window
//and quit sdl.
void Renderer::cleanup()
{
    ghge_window -> cleanup();
    SDL_Quit();
}

<<<<<<< HEAD
=======
//Initialzie SDL for video.
void Renderer::init()
{



    // Step 1: Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return;
    }

    // Step 2: Set OpenGL version and profile (e.g., OpenGL 3.3 Core)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // Step 3: Create an SDL window with OpenGL support
    window = SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			      winWidth, winHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    // Step 4: Create an OpenGL context associated with the SDL window
    context = SDL_GL_CreateContext(window);
    if (!context) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // Step 5: Initialize GLEW (after creating the OpenGL context)
    glewExperimental = GL_TRUE;  // Enable modern OpenGL features
    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(glewStatus) << std::endl;
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // Check OpenGL and GLEW versions
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;

    const char* renderer = (const char*)glGetString(GL_RENDERER);  // GPU renderer name
    const char* vendor = (const char*)glGetString(GL_VENDOR);      // GPU vendor name
    const char* version = (const char*)glGetString(GL_VERSION);    // OpenGL version
    const char* extensions = (const char*)glGetString(GL_EXTENSIONS); // Supported extensions

    printf("GPU Renderer: %s\n", renderer);
    printf("GPU Vendor: %s\n", vendor);
    printf("OpenGL Version: %s\n", version);
    printf("Supported Extensions: %s\n", extensions);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    return;
}
>>>>>>> main

//swap the window.
void Renderer::swapwindow()
{
	if( ghge_window == nullptr ) 
	{
		std::cerr << "Error: ghge window not defined" << std::endl;
		return;
	}

	SDL_GL_SwapWindow(  ghge_window -> getSdlWindow() );
}

//Set the shader to the shader pointer passed into the function.
void Renderer::setShader(Shader *shader_)
{
	shader = shader_;
}
