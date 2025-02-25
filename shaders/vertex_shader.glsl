#version 330 core

layout(location = 0) in vec3 aPos;    // Vertex position
layout(location = 1) in vec3 aNormal; // Vertex normal

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float t_value;

out vec3 FragPos_view;
out vec3 Normal_view;

vec4 calculateProjection(vec4 posInWorld)
{
    // Convert position to view space
    FragPos_view = vec3(view * posInWorld);

    
    // Transform normal into view space correctly
    Normal_view = normalize(mat3(view * model) * aNormal);

    // Final position in clip space
    return projection * vec4(FragPos_view, 1.0);

}

void main() {
    // Convert vertex position to world space
    vec4 fragPos_world = model * vec4(aPos, 1.0);

    //This the actual place where you mess with position.. anything else is 
    //going to do weird things.

    fragPos_world += vec4(0.0, 0.14 * sin(t_value * 1.0 + fragPos_world.x * 2.0 + fragPos_world.z * 2.0), 0.0, 0.0);




     
    gl_Position = calculateProjection(fragPos_world);
    //gl_Position += vec4(vec3(0.0, sin(t_value), 0.0), 0.0);
}
