#include "shader.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <iostream>

void Shader::use()
{
	glUseProgram(id);
}

void Shader::setFloat(const char* field, float value)
{
	glUniform1f(glGetUniformLocation(id, field), value);
}

void Shader::setVec3(const char* field, const glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(id, field), 1, &value[0]);
}

void Shader::setMat4(const char* field, const glm::mat4& value)
{
	glUniformMatrix4fv(glGetUniformLocation(id, field), 1, GL_FALSE, &value[0][0]);
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	id = glCreateProgram();

	unsigned v = build(GL_VERTEX_SHADER, vertexPath);
	unsigned f = build(GL_FRAGMENT_SHADER, fragmentPath);

	glAttachShader(id, v);
	glAttachShader(id, f);

	glLinkProgram(id);

	int ok;

	glGetProgramiv(id, GL_LINK_STATUS, &ok);

	if (!ok) {
		char log[512];
		glGetProgramInfoLog(id, 512, nullptr, log);
		std::cerr << "An error occured while linking shaders:\n" << log;
	}
	else {
		std::cout << "Shader has been linked successfully!\n";
	}

	glDeleteShader(v);
	glDeleteShader(f);
}

unsigned Shader::build(GLenum type, const char* path)
{
	unsigned s = glCreateShader(type);
	std::ifstream in(path);

	if (!in.is_open()) {
		std::cerr << "File with path " << path << " could not be opened / read sucessfully!\n";
	}
	else {
		std::cout << "File with path " << path << " opened successfully!\n";
	}

	std::stringstream stream;
	stream << in.rdbuf();
	std::string string = stream.str();
	const char* raw = string.c_str();

	glShaderSource(s, 1, &raw, nullptr);

	glCompileShader(s);

	int ok;

	glGetShaderiv(s, GL_COMPILE_STATUS, &ok);

	if (!ok) {
		char log[512];
		glGetShaderInfoLog(s, 512, nullptr, log);
		std::cerr << "Shader at path " << path << " caused at least one error while compiling:\n" << log;
	}
	else {
		std::cout << "Shader at path " << path << " compiled successfully!\n";
	}

	return s;
}
