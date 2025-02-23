//  ObjFile reader implementation
//
//
//  (C) Garrett Hannah, 2024
//
//  INSTRUCTIONS:
//  1. Create OBJ reader. (construct)
//  2. set obj file path. (openOBJfile)
//  3. read() function.
//
//  then youll want to pull vert and whatnot data from 
//  the verts and indices parameters. 
//
//  of course i should be making this better but oh well.
//  Im also not sure how well kept everything is 
//  in terms of like, (stuff) but oh well.
//
//  So mostly i should probably focus on something
//  actually important. Like the fact that i have 
//  absolutely zero (and i mean ZERO) clue about 
//  what i have going on with deep copies and whatnot.
//
//  Especially with like data deletion and stuff. that 
//  is not at all created or anything.
//  so im probably cooked
//
//  Anyways this little bit of code works well enough 
//  indeed that i can just use it in my program
//  without really caring at all! yay.

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
//This is just calculated based on the min values, then normalizing it and dividing it into a semi standardized size.
//Idk it works lol
glm::vec3 ObjReader::getNormScale()
{
    float meshSize = glm::length(glm::vec3(mxX, mxY, mxZ) - glm::vec3(mnX, mnY, mnZ)); 
    
    if(meshSize == 0) return glm::vec3(1.0);
    return glm::vec3(1 / meshSize); 
}



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
            
            vals[i] = (GLuint)stoi(chunk) - 1;
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
        while(getline(objFile, line))
        {
            if(line.empty()) continue;

            switch(line[0])
            {
                case 'v': {
                    Vertex v = parseVertexLine(line);
                    
                    mnX = std::min(v.Position.x, mnX);
                    mnY = std::min(v.Position.y, mnY);
                    mnZ = std::min(v.Position.z, mnZ);

                    mxX = std::max(v.Position.x, mnX);
                    mxY = std::max(v.Position.y, mnY);
                    mxZ = std::max(v.Position.z, mnZ);

                    verts.push_back(v);
                    break;
                }
                
                case 'f': {
                    GLuint* faceIndices = parseFaceLine(line);
                    
                    this -> indices.push_back(faceIndices[0]);
                    this -> indices.push_back(faceIndices[1]);
                    this -> indices.push_back(faceIndices[2]);

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
    std::cout << i << " lines. Completed Reading." << std::endl;
};
