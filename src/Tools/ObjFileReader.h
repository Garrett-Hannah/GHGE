//Objfile reader class.
//
//  (C) Garrett Hannah, 2024
//
//This class should provide utility for being able to export a 3d object
//as a .obj file, and will then create a mesh object from it...

//	How Will our fileReader work?
//
// Our filereader will be initialized. once, initialized, it will
// be able to set it's path. when a path is set, it will be able to open, and convert to a mesh.
// This will be stored in our meshBuffer.


#include <fstream>  //File I/O operations
#include <sstream>
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <stdexcept>
#include <sys/types.h>
#include <algorithm>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#pragma once

#include "../src/Mesh.h"

class ObjReader
{
	protected:
	std::string readPath = "";
	bool validReadPath = false;
	Vertex parseVertexLine(std::string line);
	GLuint* parseFaceLine(std::string line);
	
    int lineCount = 0;

    float mnX, mnY, mnZ, mxX, mxY, mxZ;

	public:
	
    ObjReader();
	std::vector<Vertex> verts;
	std::vector<GLuint> indices;

       
    glm::vec3 getNormScale();
    //Out OpenObjFile will read our path.
	bool openObjFile(std::string path);
	//Return Our MeshBuffer As a mesh.
	//This will write from our file into our mesh buffer.
	int writeToMeshBuffer();
	void read();
};
