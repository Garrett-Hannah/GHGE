#version 330

in vec3 FragNormal;
out vec4 FragColor;

void main() {
    vec3 color = normalize(FragNormal) * 0.5 + 0.5;
    FragColor = vec4(vec3( FragNormal.x, FragNormal.y, FragNormal.z), 1.0);
    
}
