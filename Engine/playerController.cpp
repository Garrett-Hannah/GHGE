#include "playerController.h"

void Controller::ProcessUpdate()
{
        currentPos = glm::vec3(0);
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
	    if ( inputManager -> shift() )
	    {
		    translation += glm::vec3(0.0f, -1.0f, 0.0f);
	    }

	    if (inputManager -> isKeyPressed( KEY_O ))
	    {
		    this -> camYaw += 0.01f;
	    }

	    if (inputManager -> isKeyPressed( KEY_P ))
	    {
		    camYaw -= 0.01f;
	    }

        if (inputManager -> isKeyPressed( KEY_MINUS ))
        {
            camPitch -= 0.01f;
        }
        if (inputManager -> isKeyPressed( KEY_EQUALS ))
        {
            camPitch += 0.01f;
        }

        currentPos = translation;
}
