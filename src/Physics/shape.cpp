// (C) Garrett Hannah you know the rest 
// (2025)!
//

#include "shape.h"

namespace GHGE{
    //Function for colliding
    bool collide(const sphere& s1, const sphere& s2)
    {
        glm::vec3 v3_dist = s2.position - s1.position;
       
        float distSquared = 0;

        for(int i = 0; i < 3; i++){
            distSquared += v3_dist[i] * v3_dist[i];
        }

        return distSquared <= (s2.radius + s1.radius);
    }
}
