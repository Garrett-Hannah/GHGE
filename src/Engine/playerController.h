#include "inputManager.h"
#include <glm/ext/matrix_float4x4.hpp>

class Controller
{
    public:    
    glm::vec3 currentPos;
    float camYaw = 0.25f;
    float camPitch = 0.5f;

    InputManager* inputManager;

    void ProcessUpdate();
    
    glm::vec3 getMoveDir();

    Controller(InputManager* manager)
    {
        inputManager = manager;
    }

    glm::vec3 getCameraTarget(const glm::vec3& camPos);


    glm::vec3 getTranslation();

    private:
        int oldMouseX;
        int oldMouseY;


};
