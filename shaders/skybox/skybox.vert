#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 uView;
uniform mat4 uProj;
uniform mat4 uModel;

out vec3 TexCoord;

void main() {
    TexCoord = aPos;
    gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);
}