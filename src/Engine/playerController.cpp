#include "playerController.h"

glm::vec3 Controller::getMoveDir()
{
        glm::vec3 translation(0.0f);
	    
    
        if (inputManager -> isKeyPressed( KEY_W ))
	    {
		    translation += glm::vec3(0.0f, 0.0f, 1.0f);
	    }
	    
        if (inputManager -> isKeyPressed( KEY_A ) )
	    {
		    translation += glm::vec3(1.0f, 0.0f, 0.0f);
	    }
	    
        if (inputManager -> isKeyPressed( KEY_S ))
	    {
		    translation += glm::vec3(0.0f, 0.0f, -1.0f);
	    }

	    if (inputManager -> isKeyPressed( KEY_D ))
	    {
		    translation += glm::vec3(-1.0f, 0.0f, 0.0f);
	    }    
	    if (inputManager -> isKeyPressed( KEY_SPACE ))
        {
		    translation += glm::vec3(0.0f, 1.0f, 0.0f);
	    }
        if ( inputManager -> isKeyPressed( KEY_LEFT_SHIFT ) )
	    {
		    translation += glm::vec3(0.0f, -1.0f, 0.0f);
	    }

        return translation;
}

glm::vec3 Controller::getCameraTarget(const glm::vec3& camPos)
{
        camYaw += inputManager -> getMouseVelX();
        camPitch += inputManager -> getMouseVelY();
                
        glm::vec3 camRotation;
        camRotation.z = std::cos(camYaw) * std::cos(camPitch);
        camRotation.y = std::sin(camPitch);
        camRotation.x = std::sin(camYaw) * std::cos(camPitch);

        return camPos + glm::normalize(camRotation);
}

void Controller::ProcessUpdate()
{
    currentPos *= 0.95;
    if(inputManager == nullptr) return;

        camYaw -= float(inputManager -> getMouseVelX()) / 150.0f;    
        camPitch -= float(inputManager -> getMouseVelY()) / 300.0f;

	    if (inputManager -> isKeyPressed( KEY_O ))
	    {
		    camYaw += 0.01f;
	    }

	    if (inputManager -> isKeyPressed( KEY_P ))
	    {
		    camYaw -= 0.01f;
	    }

        if (inputManager -> isKeyPressed( KEY_MINUS ))
            camPitch -= 0.01f;

        if (inputManager -> isKeyPressed( KEY_0))
            camPitch += 0.01f;
        
        if (inputManager -> isKeyPressed( KEY_R ))
        {
            this -> camPitch = 0.0f;
            this -> camYaw = 0.0f;
            this -> currentPos = glm::vec3(0.0f, 0.0f, 0.0f); 
        }

        currentPos += getMoveDir();
}

