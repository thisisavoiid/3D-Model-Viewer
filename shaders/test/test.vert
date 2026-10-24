#version 330 core

layout(location = 0) in vec3 aPos;

out vec3 vColor;
uniform mat4 uModel;
uniform mat4 uProj;
uniform mat4 uView;

void main() {
    gl_Position = uProj * uView * uModel * vec4(aPos,1.0);

    vColor = vec3(1.0, 0.5, 1.0);
}