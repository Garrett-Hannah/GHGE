#include "Tools/ObjFileReader.h"
#include <stdexcept>

void writeVec(const Vertex &v)
{
    std::cout << v.Position.x << " " << v.Position.y << " " << v.Position.z << std::endl;
}


class objReaderTests : ObjReader
{
    public:
   

    bool testLine(const std::string &s)
    {
        Vertex v1;
        try {
            v1 = this -> parseVertexLine(s);
        }
        catch(const std::invalid_argument &e)
        {
            std::cout << e.what() << std::endl;
            return false;
        }

        std::cout << "\"" << s << "\"" << " -> Parsed valid line:";
        writeVec(v1);

        return true;
    }

    bool testClass() 
   {
       ObjReader r;

        std::string validLine = "v 1.0 2.0 3.0";
        std::string extraSpaces = "v 0  0  0";
        std::string missingValues = "v 0";
        std::string malformedLine = "v 0 abc 1";
        std::string toomanyValues = "v 1.0 2.0 3.0 4.0";
        bool result = true;

        result = result && testLine(validLine);
        result = result && testLine(extraSpaces);
        result = result && testLine(missingValues);
        result = result && !testLine(malformedLine);
        result = result && testLine(toomanyValues);




        return result;
   }
};

int main()
{
    objReaderTests readerTest;
    
    std::cout << readerTest.testClass();
}
