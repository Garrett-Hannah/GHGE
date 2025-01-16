//ObjFile reader implementation
//
//
//  (C) Garrett Hannah, 2024
//
//  This is our implementation for the objreader.
#include "ObjFileReader.h"


//set validReadPath to nothing and create a mesh.
ObjReader::ObjReader()
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


//read from the .obj file into our mesh object.
void ObjReader::writeToMeshBuffer()
{
    //If we dont have a valid read path, return
    if(!validReadPath)
    {
        std::cout << "Failed!" << std::endl;
        return;
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
	GLuint* indArr;


        //Using the first char from each line, execute seperate functions.
        switch(line[0])
        {
            // vertex info:
            case 'v':
                vTemp = parseVertexLine(line);
                verts.push_back(vTemp);

            break;

            //face info:
            case 'f':
            	indArr = parseFaceLine(line);
		indicies.push_back(indArr[0]);
		indicies.push_back(indArr[1]);
		indicies.push_back(indArr[2]);
	    break;
        }
	lineCount++;
    }

    std::cout << lineCount << " lines in file!" << std::endl;


};


//ParseVertextLine
//
//Takes a string line, and returns vertex object.
Vertex ObjReader::parseVertexLine(std::string line)
{
    //Start at the beginning of the first whitespace. find the next after.
    size_t flStart = line.find(" ");
    size_t flEnd = line.find(" ", flStart + 1);

    //Create an array of 3 floats.
    float v[3];

    //Iterate over each value in fVals, and convert string to float.
    for(int i = 0; i < 3; i++)
    {
        std::string sub = line.substr(flStart, flEnd - flStart);

        v[i] = stof(sub);

        flStart = flEnd;
        flEnd = line.find(" ", flStart + 1);
    }

    

  //Return vert.
    return {{v[0], v[1], v[2]}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}};
}


//Face line parse.
GLuint* ObjReader::parseFaceLine(std::string line)
{
    size_t iStart = line.find(" ");
    size_t iEnd = line.find(" ", iStart + 1);

    GLuint* vals = new GLuint[3];

    for(int i = 0; i < 3; i++)
    {

        std::string sub = line.substr(iStart, iEnd - iStart);

        vals[i] = stoi(sub) - 1;

	indicies.push_back(vals[i]);
        iStart = iEnd;
        iEnd = line.find(" ", iStart + 1);
    }

    //As of right now, the expectation is that were gonna be returning
    //some values.
    
    return vals;
}


//Given that we have a valid read path,
//Parse each line. as of right now, we will only support v or f commands.
void ObjReader::read()
{
	if(!validReadPath)
	{
		std::cout << "Err: Invalid readPath! Try again. " << std::endl;
		return;
	}


	std::ifstream objFile;
	objFile.open(readPath);

	std::string line;

	int i = 0;
	while(getline(objFile, line) && i < 10)
	{
		switch(line[0])
		{
			case 'v':
				parseVertexLine(line);
			break;

			case 'f':
				parseFaceLine(line);
			break;
		}
		i++;
	}

	objFile.close();
};
