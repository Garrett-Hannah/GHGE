//ObjFile reader implementation
//
//
//  (C) Garrett Hannah, 2024
//
//  This is our implementation for the objreader.
#include "ObjFileReader.h"

//set validReadPath to nothing and create a mesh.
ObjReader::ObjReader() : validReadPath(false)
{
	std::cout << "ObjectFileReader Initialized!" << std::endl;
	validReadPath = false;
};


//Initialize our filereader onto path.
bool ObjReader::openObjFile(std::string path)
{
	if(path.rfind(".obj") == std::string::npos)
	{
		std::cout << "Error: File is not of .obj extension. Terminating." << std:: endl;
		return false;
	}


	std::cout << path << std::endl;
	readPath = path;
	validReadPath = true;

	return true;

};

//Returns a normalized version of the scale...
glm::vec3 ObjReader::getNormScale()
{
    float meshSize = glm::length(glm::vec3(mxX, mxY, mxZ) - glm::vec3(mnX, mnY, mnZ)); 
    
    if(meshSize == 0) return glm::vec3(1.0);
    return glm::vec3(1 / meshSize); 
}

/*
//read from the .obj file into our mesh object.
int ObjReader::writeToMeshBuffer()
{
    //If we dont have a valid read path, return
    if(!validReadPath)
    {
        std::cout << "Failed!" << std::endl;
        return -1;
    }
	

    lineCount = 0;
    //create an inputstream and open the file.
    std::ifstream objFile;
    objFile.open(readPath);

    //Store lines from file in a string
    std::string line;

    //Loop through each line in the .obj file.
    //there is two commands important to us.
    //1) 'v' - this implies a vertex in 3d space.
    //2) 'f' - this implies a face, printed from _ - _ - _.
    // NOTE: 2 is having troubles so far. i believe it has to do with
    // the way that i draw lines.
    while(getline(objFile, line))
    {
        //Create some temp variables.
	Vertex vTemp;
	GLuint* indArr = new GLuint[3];


        //Using the first char from each line, execute seperate functions.
        switch(line[0])
        {
            // vertex info:
            case 'v':
                vTemp = parseVertexLine(line);
                mnX = std::min(mnX, vTemp.Position.x);
                mnY = std::min(mnY, vTemp.Position.y);
                mnZ = std::min(mnZ, vTemp.Position.z);
                
                mxX = std::max(mxX, vTemp.Position.x);
                mxY = std::max(mxY, vTemp.Position.y);
                mxZ = std::max(mxZ, vTemp.Position.z);
                verts.push_back(vTemp);

            break;

            //face info:
            case 'f':
            	indArr = parseFaceLine(line);
		        indices.push_back(indArr[0]);
		        indices.push_back(indArr[1]);
		        indices.push_back(indArr[2]);
	        break;
        }

	    lineCount++;
    }

    std::cout << lineCount << " lines in " << this -> readPath << std::endl;

    return 1;
};*/


//ParseVertextLine
//
//Takes a string line, and returns vertex object.
Vertex ObjReader::parseVertexLine(std::string line)
{
    std::stringstream stream(line);
    stream.exceptions(std::ios::badbit);

    std::string chunk;
    
    stream >> chunk;

    Vertex v = {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0, 0}};

    int i = 0;
    try{
        while(stream >> chunk && i < 3){  
            if(std::any_of(chunk.begin(), chunk.end(), ::isalpha)){
                throw std::invalid_argument("Non-numeric chunk: " + chunk);
            }
            
            v.Position[i] = stof(chunk);
            i++;
        }
    }
    catch(const std::ios_base::failure& e)
    {
        std::cerr << "Stream error: " << e.what() << std::endl;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << "Conversion error: invalid argument: " << e.what() << std::endl;
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << "Conversion error: out of range: " << e.what() << std::endl;
    }

    if(i < 3) std::cerr << "WARNING: Vertex contians missing values: " << line << std::endl;


    return v;
}


//Face line parse.
GLuint* ObjReader::parseFaceLine(std::string line)
{

    std::stringstream stream(line);
    stream.exceptions(std::ios::badbit);

    std::string chunk;
    
    stream >> chunk;

    GLuint* vals = new GLuint[3];

    int i = 0;

    try{
        while(stream >> chunk && i < 3){  
            if(std::any_of(chunk.begin(), chunk.end(), ::isalpha)){
                throw std::invalid_argument("Non-numeric chunk: " + chunk);
            }
            
            vals[i] = (GLuint)stoi(chunk);
            i++;
        }
    }
    catch(const std::ios_base::failure& e)
    {
        std::cerr << "Stream error: " << e.what() << std::endl;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << "Conversion error: invalid argument: " << e.what() << std::endl;
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << "Conversion error: out of range: " << e.what() << std::endl;
    }

    if(i < 3) std::cerr << "WARNING: Vertex contians missing values: " << line << std::endl;


    return vals;
}


//Given that we have a valid read path,
//Parse each line. as of right now, we will only support v or f commands.
void ObjReader::read()
{
	if(!validReadPath)
	{
		std::cerr << "Err: Invalid readPath! Try again. " << std::endl;
		return;
	}


	std::ifstream objFile(readPath);
    if (!objFile.is_open()){
        std::cerr << "Err: Unable to open file : " << readPath << std::endl;
        return;
    }

	std::string line;
	int i = 0;

    try{
        while(getline(objFile, line) && i < 10)
        {
            if(line.empty()) continue;

            switch(line[0])
            {
                case 'v': {
                    Vertex v = parseVertexLine(line);
                    verts.push_back(v);
                    break;
                }
                case 'f': {
                    GLuint* faceIndices = parseFaceLine(line);
                    
                    for(int i = 0; i < 3; i++) this -> indices.push_back(faceIndices[i]);

                    delete[] faceIndices;

                    break;
                
                }
                
                default:
                    std::cerr << "Warning: Unsupported line type: " << line << std::endl;
            
            }
            i++;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error parsing OBJ file: " << e.what() << " (line " << i << ")" << std::endl;
    }

	objFile.close();
};
