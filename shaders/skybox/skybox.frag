#version 330 core

in vec3 TexCoord;

uniform samplerCube uSkybox;

out vec4 FragColor;

void main() {
    FragColor = texture(uSkybox, TexCoord);
}