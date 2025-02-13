#include "../src/Mesh.h"
#include "inputManager.h"

class Controller
{
    public:    
    glm::vec3 currentPos;
    float camYaw = 0.0f;
    float camPitch = 0.0f;

    InputManager* inputManager;

    void ProcessUpdate();
    
    glm::vec3 getMoveDir();

    Controller(InputManager* manager)
    {
        inputManager = manager;
    }

    glm::vec3 getCameraTarget(const glm::vec3& camPos);

    private:
        int oldMouseX;
        int oldMouseY;

};
