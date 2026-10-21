#version 330 core

layout(location = 0) in vec3 aPos;

out vec3 vColor;
uniform float uTime;
uniform float uSpeed;

void main() {
    gl_Position = vec4(aPos, 1.0);

    vColor = vec3(1.0, 0.5, 1.0)
           * (0.5 + 0.5 * sin(uTime * uSpeed));
}