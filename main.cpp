#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include <cmath>


#include "src/Renderer.h"
#include "src/Mesh.h"
#include "src/Camera.h"

#include "Engine/input.h"

#include "Tools/ObjFileReader.h"

//Notes changes 

GLfloat camYaw = 0.0f;
GLfloat camPitch = 0.0f;
GLfloat dt = 0.0f;

GLuint SCR_WIDTH, SCR_HEIGHT;

bool addT = false;

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




GLuint inds[] = 
{
		0, 1, 2,
		0, 2, 3	
};

unsigned int VAO;

void bgSetup()
{
	unsigned int VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind VAO
	glBindVertexArray(VAO);
	
	// Bind VBO and buffer the vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	
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



float bgTime = 0.0f;

//As of right now, this is not working. 
void bgDraw(Shader* shader)
{

	bgTime += 0.001f;

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

glm::vec3 inputUpdate(Input &input)
{
    	glm::vec3 translation(0.0f);
	    if (input.isKeyPressed( SDL_SCANCODE_W ))
	    {
		    translation += glm::vec3(0.0f, 0.0f, 1.0f);
	    }
	    if (input.isKeyPressed( SDL_SCANCODE_A ) )
	    {
		    translation += glm::vec3(1.0f, 0.0f, 0.0f);
	    }
	    if (input.isKeyPressed( SDL_SCANCODE_S ))
	    {
		    translation += glm::vec3(0.0f, 0.0f, -1.0f);
	    }
	    if (input.isKeyPressed( SDL_SCANCODE_D ))
	    {
		    translation += glm::vec3(-1.0f, 0.0f, 0.0f);
	    }
	    if (input.isKeyPressed( SDL_SCANCODE_SPACE ))
	    {
		    translation += glm::vec3(0.0f, 1.0f, 0.0f);
	    }
	    if (input.isKeyPressed( SDL_SCANCODE_LSHIFT ))
	    {
		    translation += glm::vec3(0.0f, -1.0f, 0.0f);
	    }

	    if (input.isKeyPressed( SDL_SCANCODE_O ))
	    {
		    camYaw += 0.01f;
	    }

	    if (input.isKeyPressed( SDL_SCANCODE_P ))
	    {
		    camYaw -= 0.01f;
	    }

        if (input.isKeyPressed( SDL_SCANCODE_MINUS ))
        {
            camPitch -= 0.01f;
        }
        if (input.isKeyPressed( SDL_SCANCODE_EQUALS ))
        {
            camPitch += 0.01f;
        }

	    if (input.isKeyPressed( SDL_SCANCODE_T ))
	    {
		    addT = true;
	    }

	    return translation;
}

void setup_hdrFBO(GLuint &hdrFBO)
{
    // set up floating point framebuffer to render scene to
    glGenFramebuffers(1, &hdrFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    unsigned int colorBuffers[2];
    glGenTextures(2, colorBuffers);
    for (unsigned int i = 0; i < 2; i++)
    {
        glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // attach texture to framebuffer
        glFramebufferTexture2D(
            GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0
        );
    }
}



//This should be redone into something better.
//I think an event queue would be interesting.
//Or at minimum an array of active keys.
int main(int argc, char* argv[]) {


    //Enter program
	std::cout << "Program entered!" << std::endl;

    //Declare width and height values.
	GLuint w, h;
    	w = 1600;
    	h = 1200;
    
    //Initialize the renderer.
    Renderer renderer(w, h);


	std::cout << "Initialzied!" << std::endl;

    std::vector<Shader*> shaders;
    std::vector<Mesh*> meshes;

    shaders.push_back(new Shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl"));

	std::cout << "Shaders Created" << std::endl;

	renderer.setShader(shaders[0]);

	std::cout << "Shader Set!" << std::endl;

	

	glClearColor(0.28f, 0.4f, 0.75f, 1.0f);
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	ObjReader r = ObjReader();

    

	r.openObjFile("data/xyzrgb_dragon.obj");

	r.writeToMeshBuffer();

	vertices = r.verts;
	indices = r.indicies;

	std::vector<Texture> textures;
	textures.push_back({1, "texture"});

	//mesh.calculateNormals();
	meshes.push_back(new Mesh(vertices, indices, textures));
	
	
	shaders.push_back(new Shader("shaders/bgVshader.glsl", "shaders/bgFshader.glsl"));
	

    meshes[0] -> modelScale = glm::vec3(0.250f, 0.250f, 0.250f);
	
    bgSetup();

    std::vector<Vertex> vertices2 = {
        {{-10.0f,  0.0f, 10.0f}, { 0.0f,  0.0,  0.0f}, {0.0f, 1.0f}}, // Top-left (Top face)
        {{ 10.0f,  0.0f, 10.0f}, { 0.0f,  0.0f,  0.0f}, {1.0f, 1.0f}}, // Top-right
        {{ -10.0f,  0.0f,  -10.0f}, { 0.0f,  0.0f,  0.0f}, {1.0f, 0.0f}}, // Bottom-right
        {{10.0f,  0.0f,  -10.0f}, { 0.0f,  0.0f,  0.0f}, {0.0f, 0.0f}}, // Bottom-left
    };

    std::vector<GLuint> indices2 = {
        0, 1, 2, 2, 1, 3
    };




    meshes.push_back( new Mesh( vertices2, indices2, textures ) );



    unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, attachments); 


	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::vec3 camPos = glm::vec3( -1.0f, 0.0f, 0.0f );


	glm::vec3 translation( 0.0f, 0.0f, 0.0f );
    	bool running = true;
	 
    Input input;

    while ( running ) {

	translation = glm::vec3( 0.0f );
	SDL_Event event;
        while ( SDL_PollEvent( &event ) )
        {
            if ( event.type == SDL_QUIT ) running = false;
            if ( event.type == SDL_KEYDOWN || event.type == SDL_KEYUP ) 
            {
                input.updateKeys( &event );
            }
	}

	translation = inputUpdate(input);
	translation = translation * 0.25f;
	
	glm::quat rotationQuat = glm::angleAxis(camYaw, glm::vec3(0.0f, 1.0f, 0.0f));

		translation = rotationQuat * translation;


    	if(addT)dt += 0.01f;
	glm::vec3 mPos = glm::vec3(std::sin(dt), std::cos(dt) * 3, 0.0f);

	meshes[0] -> modelPosition = mPos;

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translation);

	// Apply the translation by multiplying the matrix and the vector
	glm::vec4 translatedVec = translationMatrix * glm::vec4(camPos, 1.0f);

	// If you need a glm::vec3 result (ignoring the w-component), you can convert it back:
	camPos = glm::vec3(translatedVec);
		// Render here


	camera.setPosition( camPos );

	camera.setTarget( camPos + glm::vec3(std::sin(camYaw), std::sin(camPitch), std::cos(camYaw)));


    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	bgDraw(shaders[1]);
	
    GLenum error = glGetError();

	while(error != GL_NO_ERROR)
	{
		std::cerr << "Opengl Error: " << error << std::endl;
		error = glGetError();
	}
	
    for(Mesh* mesh : meshes )
    {
        renderer.render(*mesh, camera);
    }

	renderer.swapwindow();  // Swap buffers
    }

    renderer.cleanup();

    return 0;
}
