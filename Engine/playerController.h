#include "../src/Mesh.h"
#include "inputManager.h"

class Controller
{
    public:    
    glm::vec3 currentPos;
    float camYaw;
    float camPitch;

    InputManager* inputManager;

    void ProcessUpdate();
    
    glm::vec3 getMoveDir();

    Controller(InputManager* manager)
    {
        inputManager = manager;
    }

    private:
        int oldMouseX;
        int oldMouseY;

};
