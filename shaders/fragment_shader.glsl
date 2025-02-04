//Fragment shader for basic models...
#version 330

in vec3 FragNormal;
in vec3 FragPosition;

in float tcolor;


out vec4 FragColor;

uniform vec3 lightPos;

float roundToTenth(float val)
{
    return round(val * 10.0) / 10.0;
}

vec4 getLightVal(vec3 fragNorm, vec3 lDir)
{
    float lightVal = max(dot(fragNorm, lDir), 0.0);

    vec4 v4LightVal = vec4(vec3(lightVal), 1.0);

    return v4LightVal;
}

void main() {
    vec3 lightDir = vec3(sin(tcolor), -1.0 , cos(tcolor) );
    //float distance = length(FragPosition - lightPos);
   
    FragColor = getLightVal(FragNormal, lightDir);

    if(FragPosition.x > sin(tcolor * 0.1) * 67.5)
        FragColor *= vec4(1.0, 0.0, 0.0, 1.0);
    else
        FragColor *= vec4(0.0, 0.0, 1.0, 1.0);
    
    
}
