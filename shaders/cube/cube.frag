#version 330 core

in vec3 Normal;
in vec3 FragPos;  
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 uObjectColor;
uniform vec3 uLightColor;
uniform vec3 uLightPos;
uniform sampler2D uTexture;

void main() {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * uLightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(uLightPos-FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff*uLightColor;

    vec4 result = vec4(ambient+diffuse, 1.0);
    
    FragColor = texture(uTexture, TexCoord) * result;
}