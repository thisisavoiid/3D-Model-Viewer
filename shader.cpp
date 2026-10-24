#include "shader.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <iostream>

/// <summary>
/// Activates this shader program for subsequent rendering calls.
/// </summary>
void Shader::use()
{
	glUseProgram(id);
}

/// <summary>
/// Sets a float uniform value in the shader.
/// </summary>
/// <param name="field">
/// The name of the uniform variable.
/// </param>
/// <param name="value">
/// The float value to assign to the uniform.
/// </param>
void Shader::setFloat(const char* field, float value)
{
	glUniform1f(glGetUniformLocation(id, field), value);
}

/// <summary>
/// Sets a vec3 uniform value in the shader.
/// </summary>
/// <param name="field">
/// The name of the uniform variable.
/// </param>
/// <param name="value">
/// The glm::vec3 value to assign to the uniform.
/// </param>
void Shader::setVec3(const char* field, const glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(id, field), 1, &value[0]);
}

/// <summary>
/// Sets a mat4 uniform value in the shader.
/// </summary>
/// <param name="field">
/// The name of the uniform variable.
/// </param>
/// <param name="value">
/// The glm::mat4 value to assign to the uniform.
/// </param>
void Shader::setMat4(const char* field, const glm::mat4& value)
{
	glUniformMatrix4fv(glGetUniformLocation(id, field), 1, GL_FALSE, &value[0][0]);
}

/// <summary>
/// Constructs a shader program by compiling and linking the given vertex and fragment shader files.
/// </summary>
/// <param name="vertexPath">
/// Path to the vertex shader source file.
/// </param>
/// <param name="fragmentPath">
/// Path to the fragment shader source file.
/// </param>
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

/// <summary>
/// Compiles a single shader of the specified type from the given source file.
/// </summary>
/// <param name="type">
/// The OpenGL shader type (e.g. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER).
/// </param>
/// <param name="path">
/// Path to the shader source file.
/// </param>
/// <returns>
/// The compiled OpenGL shader object ID.
/// </returns>
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