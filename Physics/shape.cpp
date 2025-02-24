// (C) Garrett Hannah you know the rest 
// (2025)!
//

#include "shape.h"

bool GHGE::collide(const GHGE::sphere &s1, const GHGE::sphere &s2)
{
        glm::vec3 v3_dist = s2.position - s1.position;


        return v3_dist.length() < (s2.radius + s1.radius);
}
