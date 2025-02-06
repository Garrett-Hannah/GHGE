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


float clampToMax(float val, float max, float threshold)
{
    return mix(val, max, step(max - threshold, val));
}

vec4 getLightVal(vec3 fragNorm, vec3 lDir)
{
    float lightVal = max(dot(fragNorm, lDir), 0.0);

    vec4 v4LightVal = vec4(vec3(lightVal), 1.0);

    return v4LightVal;
}

void main() {
    vec3 lightDir = vec3(sin(tcolor) * 0.25, -1.0, 0.0);
    lightDir = normalize(lightDir);
    //float distance = length(FragPosition - lightPos);
   
    vec4 lightMap = getLightVal(FragNormal, lightDir);

    vec4 refLightMap = getLightVal(FragNormal, -lightDir);

    float v = min(max(dot(FragNormal, lightDir), 0.0), 1.0);
    
    refLightMap = mix(vec4(vec3(0.0), 1.0), vec4(1.0), v);
    
    FragColor = refLightMap;
}

