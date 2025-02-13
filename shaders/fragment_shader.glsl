#version 330 core

in vec3 FragPos_view;
in vec3 Normal_view;

out vec4 FragColor;

uniform vec3 lightPos_world; // Light position in world space
uniform vec3 viewPos_world;  // Camera position in world space
uniform vec3 lightColor;     // Light color

uniform mat4 view;  // View matrix

void main() {
    // Transform the light position into view space
    vec3 lightPos_view = vec3(view * vec4(lightPos_world, 1.0));

    // Compute light direction in view space
    vec3 lightDir = normalize(lightPos_view - FragPos_view);

    // Normalize the normal vector
    vec3 normal = normalize(Normal_view);

    // Diffuse shading (Lambertian reflection)
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Specular shading (Blinn-Phong)
    vec3 viewDir = normalize(-FragPos_view); // Camera is at (0,0,0) in view space
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    // Combine ambient, diffuse, and specular lighting
    vec3 ambient = 0.1 * lightColor;
    vec3 diffuse = diff * lightColor;
    vec3 specular = spec * lightColor;

    vec3 result = ambient + diffuse + specular;
    //FragColor = vec4(result, 1.0);

    FragColor = vec4(abs(lightDir), 1.0);
    
}

