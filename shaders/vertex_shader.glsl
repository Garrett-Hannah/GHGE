#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float FARPLANE;

//Implement this when needed.
//uniform vec3 lightPoint;

out vec3 FragNormal;
out vec3 FragPosition;
out float lightVal;

out float tcolor;

mat4 BuildTranslation(vec3 delta)
{
    return mat4(
            vec4(1.0, .0, .0, .0),
            vec4(0.0, 1.0, .0, .0),
            vec4(.0, .0, 1.0, .0),
            vec4(delta, 1.0));
}

void main()
{
    tcolor = FARPLANE;
    mat4 modelP = model;
    //modelP = modelP + BuildTranslation(vec3(FARPLANE));

    gl_Position = projection * view * modelP * vec4(aPos, 1.0);
    
    FragNormal = normalize(mat3(transpose(inverse(modelP))) * aNormal);
    FragPosition = vec3(model * vec4(aPos, 1.0));
}
