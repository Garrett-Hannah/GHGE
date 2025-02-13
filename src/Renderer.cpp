#include "Renderer.h"
#include <SDL2/SDL_video.h>

//The render funciton. Takes a mesh,
//A camera, and uses the camera transforms
//to draw the mesh in 3D space.

namespace tmp
{
    float tmpVal = 0;
    glm::vec3 lightPos = glm::vec3(0.0);
};

void Renderer::render(Mesh& mesh, Camera& camera)
{
	//Get the view matrix, projection matrix.
	glm::mat4 view = camera.getViewMatrix();

	GLint winWidth, winHeight;

	winWidth = ghge_window -> getWinWidth();
	winHeight = ghge_window -> getWinHeight();

	glm::mat4 projection = camera.getProjectionMatrix(glm::radians(80.0f), (float)winWidth/winHeight, 0.1f, 450.0f);
	//Apply model transforms.
	glm::mat4 model = glm::translate(glm::mat4(1.0f), mesh.modelPosition);
	model = glm::scale(model, mesh.modelScale);
    
    //tmp::lightPos = mesh.modelPosition;
    //std::cout << tmp::lightPos.x << std::endl;

    //Use the shader attached to this renderer.
	shader -> use();
	shader -> setMat4("projection", projection);
	shader -> setMat4("view", view);
	shader -> setMat4("model", model);
    shader -> setVec3("lightPos_world", camera.TempLightPos);
    shader -> setVec3("viewPos_world", camera.getPosition()); 
  
    shader -> setVec3("lightColor", glm::vec3(0.24, 1.0, 1.0));



	//Draw the mesh with the shader.
	mesh.Draw(*shader);

	//Attempt to see if any errors had occured.
	GLenum error = glGetError();
	if(error != GL_NO_ERROR) {
		std::cout << "Opengl Error: " << error << std::endl;
	}
}


//Simply initiailze the window width/height.
Renderer::Renderer(const GLuint &winWidth_, const GLuint &winHeight_)
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

//Cleanup some of the SDL ts, like the window
//and quit sdl.
void Renderer::cleanup()
{
    ghge_window -> cleanup();
    SDL_Quit();
}

//Initialzie SDL for video.
void Renderer::init()
{
    ghge_window -> initWindow();


    // Step 2: Set OpenGL version and profile (e.g., OpenGL 3.3 Core)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // Step 3: Create an SDL window with OpenGL support
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
