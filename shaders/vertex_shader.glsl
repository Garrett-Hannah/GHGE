#version 330 core

layout(location = 0) in vec3 aPos;    // Vertex position
layout(location = 1) in vec3 aNormal; // Vertex normal

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos_view;
out vec3 Normal_view;

void main() {
    // Convert vertex position to world space
    vec4 fragPos_world = model * vec4(aPos, 1.0);

    // Convert position to view space
    FragPos_view = vec3(view * fragPos_world);

    // Transform normal into view space correctly
    Normal_view = normalize(mat3(view * model) * aNormal);

    // Final position in clip space
    gl_Position = projection * vec4(FragPos_view, 1.0);
}

