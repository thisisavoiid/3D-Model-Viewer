#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Shader {
public:
	unsigned id;
	void use();
	void setFloat(const char* field, float value);
	void setVec3(const char* field, const glm::vec3& value);
	void setMat4(const char* field, const glm::mat4& value);
	Shader(const char* vertexPath, const char* fragmentPath);
private:
	static unsigned build(GLenum type, const char* path);
};