#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Shader {
public:
	unsigned m_id;

	void Use();
	void SetFloat(const char* field, float value);
	void SetVec3(const char* field, const glm::vec3& value);
	void SetMat4(const char* field, const glm::mat4& value);
	void SetInt(const char* field, int value);
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

private:
	static unsigned Build(GLenum type, const char* path);
};