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
    mat4 modelP = model;
    //modelP = modelP + BuildTranslation(vec3(FARPLANE));
    
    tcolor = FARPLANE;

    gl_Position = projection * view * modelP * vec4(aPos, 1.0);
    

    mat3 normalMatrix = transpose(inverse(mat3(model))); 
    
    //Temporarily just the direction vector of light...
    vec3 lightPoint = vec3(sin(tcolor), sin(tcolor + 0.5), sin(tcolor * 0.9 + 1.0));
    lightPoint = normalize(lightPoint);

    FragNormal = normalize(normalMatrix * aNormal);
    
    vec3 v3gl_pos = vec3(gl_Position[0], gl_Position[1], gl_Position[2]);

    //Direction to light...
    vec3 lightDir = normalize(lightPoint - v3gl_pos);

    lightVal = abs(length(cross(FragNormal, lightDir)));
}
