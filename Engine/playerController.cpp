#include "playerController.h"

void Controller::ProcessUpdate()
{
        currentPos = glm::vec3(0);
        glm::vec3 translation(0.0f);
	    
        int inputs = 0;
        int* numInputs = inputManager -> numKeys;

	    if (inputManager -> isKeyPressed( KEY_O ))
	    {
            inputs++;
		    camYaw += 0.01f;
	    }

	    if (inputManager -> isKeyPressed( KEY_P ))
	    {
            inputs++;
		    camYaw -= 0.01f;
	    }
        


        if (inputManager -> isKeyPressed( KEY_W ))
	    {
            inputs++;
		    translation += glm::vec3(0.0f, 0.0f, 1.0f);
	    }
	    
        if (inputManager -> isKeyPressed( KEY_A ) )
	    {
            inputs++;
		    translation += glm::vec3(1.0f, 0.0f, 0.0f);
	    }
	    
        if (inputManager -> isKeyPressed( KEY_S ))
	    {
            inputs++;
		    translation += glm::vec3(0.0f, 0.0f, -1.0f);
	    }

	    if (inputManager -> isKeyPressed( KEY_D ))
	    {
            inputs++;
		    translation += glm::vec3(-1.0f, 0.0f, 0.0f);
	    }
	    if (inputManager -> isKeyPressed( KEY_SPACE ))
	    {
            inputs++;
		    translation += glm::vec3(0.0f, 1.0f, 0.0f);
	    }
	    
        if ( inputManager -> isKeyPressed( KEY_LEFT_SHIFT ) )
	    {
            inputs++;
		    translation += glm::vec3(0.0f, -1.0f, 0.0f);
	    }


        if (inputManager -> isKeyPressed( KEY_MINUS ))
        {
            inputs++;
            camPitch -= 0.01f;
        }

        if (inputManager -> isKeyPressed( KEY_EQUALS ))
        {
            inputs++;
            camPitch += 0.01f;
        }


        currentPos = translation;
}
