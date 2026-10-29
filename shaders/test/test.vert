#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUv;

out vec3 vColor;
uniform vec3 uColor;
uniform mat4 uModel;
uniform mat4 uProj;
uniform mat4 uView;

void main() {
    gl_Position = uProj * uView * uModel * vec4(aPos,1.0);
    vColor = uColor;
}