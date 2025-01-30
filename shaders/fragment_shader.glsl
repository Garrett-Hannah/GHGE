#version 330

in vec3 FragNormal;

in float tcolor;

out vec4 FragColor;

void main() {
    vec3 color = normalize(FragNormal) * 0.5 + 0.5;
    
    FragColor = vec4(vec3( tcolor * 0.5 + 0.5, 1.0 - FragNormal.y, 0.7), 1.0);
    
}
