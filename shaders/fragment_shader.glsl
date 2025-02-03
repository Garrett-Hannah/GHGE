//Fragment shader for basic models...
#version 330

in vec3 FragNormal;

in float tcolor;

in float lightVal;

out vec4 FragColor;

float roundToTenth(float val)
{
    return round(val * 10.0) / 10.0;
}

void main() {
    /*vec3 color = normalize(FragNormal) * 0.5 + 0.5;
    
    
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    float shade = abs(FragNormal.y);
        //(0.5 * sin(tcolor) + 0.5);
    float bounceLight = -FragNormal.y * 0.15;

    FragColor = vec4(bounceLight, bounceLight, bounceLight, 1.0);
    
    FragColor += vec4(shade, shade, shade, 0.0);

    FragColor *= 0.50;
    FragColor += 0.5;

    FragColor *= vec4(0.89, 0.7, 0.7, 1);
    */

    //FragColor = 0.75 * vec4(shade, shade, shade, 0.0);
    
    //float normVal = FragNormal.y;
    FragColor = vec4(lightVal, lightVal, lightVal, 1.0);
}
