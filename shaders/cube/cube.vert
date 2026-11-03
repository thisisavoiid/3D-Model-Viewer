#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;

uniform mat4 uModel;
uniform mat4 uProj;
uniform mat4 uView;

void main() {
    gl_Position = uProj * uView * uModel * vec4(aPos,1.0);
    Normal = mat3(transpose(inverse(uModel))) * aNormal;
    FragPos = vec3(uModel *vec4(aPos, 1.0));
    TexCoord = aTexCoord;
}