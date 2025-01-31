#version 330

in vec3 FragNormal;

in float tcolor;

out vec4 FragColor;

float roundToTenth(float val)
{
    return round(val * 10.0) / 10.0;
}

void main() {
    vec3 color = normalize(FragNormal) * 0.5 + 0.5;
    
    
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    float shade = FragNormal.y * 0.7;
    shade = step(0.25, shade) * roundToTenth(shade);
    FragColor -= 0.75 * vec4(shade, shade, shade, 0.0);
    
    float normVal = FragNormal.y;

    
    FragColor += vec4(0.25 * sin(tcolor * 0.2), 0.25 * sin(tcolor * 0.4), 0.25 * sin(tcolor), 0);
}
