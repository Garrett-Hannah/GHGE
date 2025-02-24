#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include <cmath>

#include "src/Renderer.h"
#include "src/Mesh.h"
#include "src/Camera.h"

#include "Engine/inputManager.h"
#include "Engine/playerController.h"

#include "Tools/ObjFileReader.h"


float dt = 0.0;

//Screen width and height values. 
GLuint SCR_WIDTH, SCR_HEIGHT;


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

//this is a VAO, for i think the backround value.
//It shouldnt be a global variable.
unsigned int VAO;

void bgSetup()
{
    //Create unsigned ints
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

//Overall i should be using maybe render layers
//of some sorts. Until then the hard-coded background
//remains. :(
void bgDraw(Shader* shader)
{
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



int main(int argc, char* argv[]) {


    //Enter program
	std::cout << "Program entered!" << std::endl;

    //Declare width and height values.
	GLuint w, h;
    	w = 1600;
    	h = 1200;
    
    //Initialize the renderer.
    Renderer renderer(w, h);

    
	std::cout << "Renderer Initialzied!" << std::endl;

    //As of right now, its just 
    //Meshes and Shader referrences being stored.
    //Its just better to have them in one spot. 
    std::vector<Shader*> shaders(2);


    shaders[0] = new Shader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    //Push back shaders for background.
    //Then setup the background vbo
    shaders[1] = (new Shader("shaders/bgVshader.glsl", "shaders/bgFshader.glsl"));
    
    std::cout << (shaders[1] != nullptr) << std::endl;

	std::cout << "Shader Created" << std::endl;

	renderer.setShader(shaders[0]);

	std::cout << "Shader Set To Renderer." << std::endl;

	//Set clear colors, and make a vertices and indices.
    //Buffer of sorts.

	glClearColor(0.28f, 0.4f, 0.75f, 1.0f);
	


    //Open up the file reader. Then store 
    //The mesh and indices in this temporary vector.
    //Overall this just puts it all together into the mesh.
    //I think it can be shortened 
    //by just returning the vert and index data 
    //as a mesh to begin with?

    ObjReader r = ObjReader();    
	r.openObjFile("data/teapot.obj");
	r.read();
    
    std::vector<Vertex> verts;
    std::vector<GLuint> inds;

    //std::cout << "written..." << std::endl;
    

    //std::vector<Vertex> vertices = r.verts;
	//std::vector<GLuint> indices = r.indices;
    
    std::cout << "a" << std::endl;

    //Push back a texture.
    //I dont even want to know how this is going
    //to be used. 
	std::vector<Texture> textures;
	textures.push_back({1, "texture"});

    //Creates a new mesh, with
    //the mesh data from earlier
    
    /*
	meshes.push_back(new Mesh(vertices, indices, textures));
    meshes[0] -> calculateNormals();
    meshes[0] -> modelScale = r.getNormScale();
    meshes[0] -> modelScale *= 10.0f;
    meshes[0] -> modelPosition += glm::vec3(0.0, 1.4, 0.0);
    /

    std::cout << "hello" << std::endl;
    meshes[0] -> setupMesh();
    */

    
    bgSetup();

    //if(meshes[0] != nullptr) std::cout << "Meshes available." << std::endl;

    //Here is just more meshes. 
    //
    //This one is just a simple plane.
    std::vector<Vertex> vertices2 = {
        {{-10.0f,  0.0f, 10.0f}, { 0.0f,  1.0,  0.0f}, {0.0f, 1.0f}}, // Top-left (Top face)
        {{ 10.0f,  0.0f, 10.0f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}}, // Top-right
        {{ -10.0f,  0.0f,  -10.0f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}}, // Bottom-right
        {{10.0f,  0.0f,  -10.0f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // Bottom-left
    };
    std::vector<GLuint> indices2 = {
        3, 1, 2, 2, 1, 0
    };
    
    verts = r.verts;
    inds = r.indices;



    Mesh mesh(verts, inds, textures);
    
    //mesh.calculateNormals();
    /*
    std::vector<Vertex> vertices3 = {
        {{-10.0f,  0.0f, 10.0f}, { 0.0f,  1.0,  0.0f}, {0.0f, 1.0f}}, // Top-left (Top face)
        {{ 10.0f,  0.0f, 10.0f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}}, // Top-right
        {{ -10.0f,  0.0f,  -10.0f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}}, // Bottom-right
        {{10.0f,  0.0f,  -10.0f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}}, // Bottom-left
    };
    std::vector<GLuint> indices3 = {
        3, 1, 2, 2, 1, 0
    };

    meshes.push_back( new Mesh( vertices3, indices3, textures) );
    
    meshes[2] -> modelScale *= 0.2;
    meshes[2] -> modelPosition += glm::vec3(0.0, 4.0, 1.0);
    //meshes[2] -> setupMesh();
    //Here is the camera initialization.	
    */

    Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::vec3 camPos = glm::vec3( -1.0f, 0.0f, 0.0f );

    


    InputManager input(renderer.getWindow());

    std::cout << "InputManager Set up..." << std::endl; 

    Controller player = Controller(&input);
    

    
	glm::vec3 translation( 0.0f, 0.0f, 0.0f );

    camera.TempLightPos = glm::vec3(0.0);
    
    //The running bool just decides when to terminate the program.
    while ( !input.quitRequested() ) 
    {
        //This is the main structure of the actual gameloop.
        //What it does is create an event, and see what has been pressed.
        //Pretty much?
    
        //First input will
        //Gather user inputs.
        //This will be used to change states of game objects.
        input.update(0, 0);
        
        //Processing the update involves calculating diffreneces (often through 
        //either inputs, Or individual object logic).
        player.ProcessUpdate();
    
        if(input.isKeyDown(KEY_J)) camera.TempLightPos += glm::vec3(0.0, 0.1f, 0.0);
        if(input.isKeyDown(KEY_K)) camera.TempLightPos += glm::vec3(0.0, -0.1f, 0.0);
        if(input.isKeyDown(KEY_B)) camera.TempLightPos += glm::vec3(0.1, 0.0, 0.0);
        if(input.isKeyDown(KEY_N)) camera.TempLightPos += glm::vec3(0.0, 0.0, -0.1);
        if(input.isKeyDown(KEY_M)) camera.TempLightPos += glm::vec3(-0.1, 0.0, 0.0);
        if(input.isKeyDown(KEY_H)) camera.TempLightPos += glm::vec3(0.0, 0.0f, 0.1);
        
        //meshes[2] -> modelPosition = camera.TempLightPos;

        translation = player.currentPos;

        translation = translation * 0.005f;
        
        
        //Really this stuff should/could be theoretically handled.
        //inside the player class itself. 
        //but its not for some reason.


        GLfloat camPitch = player.camPitch;
        GLfloat camYaw = player.camYaw;
        
        glm::quat rotationQuat = glm::angleAxis(camYaw, glm::vec3(0.0f, 1.0f, 0.0f));

        translation = rotationQuat * translation;
    
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translation);

        // Apply the translation by multiplying the matrix and the vector
        glm::vec4 translatedVec = translationMatrix * glm::vec4(camPos, 1.0f);

        // If you need a glm::vec3 result (ignoring the w-component), you can convert it back:
        camPos = glm::vec3(translatedVec);
            // Render here 

        camera.setPosition( camPos );
        
        input.getMouseVelX();
        input.getMouseVelY();


        glm::vec3 camRotation;
        camRotation.z = std::cos(camYaw) * std::cos(camPitch);
        camRotation.y = std::sin(camPitch);
        camRotation.x = std::sin(camYaw) * std::cos(camPitch);
        

        //camera.setTarget(camPos + glm::normalize(camRotation));
        camera.setTarget(camPos + glm::normalize(camRotation));

        //Clear the color bits.
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        //Draw the background.
        bgDraw(shaders[1]);
        
        
        //Final step. render the meshes.
        //This is done last, because of course it is.
        //After all, this wont be too important. 
        //Because its all done now.
        renderer.render(mesh, camera);


        //Although i might want to get some post-processing effect
        //in this, and that will drastically change code.

        //Swap windows
        //This part just does it i guess....
        renderer.swapwindow();  // Swap buffers
        
    }

        renderer.cleanup();

        return 0;
}
