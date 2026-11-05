#include "cubemap.hpp"
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <vector>
#include <iostream>

/// <summary>
/// Loads six images and creates an OpenGL cubemap texture.
/// </summary>
/// <param name="right">
/// The path to the right face image.
/// </param>
/// <param name="left">
/// The path to the left face image.
/// </param>
/// <param name="top">
/// The path to the top face image.
/// </param>
/// <param name="bottom">
/// The path to the bottom face image.
/// </param>
/// <param name="front">
/// The path to the front face image.
/// </param>
/// <param name="back">
/// The path to the back face image.
/// </param>
CubeMap::CubeMap(
	std::filesystem::path right, 
	std::filesystem::path left, 
	std::filesystem::path top, 
	std::filesystem::path bottom, 
	std::filesystem::path front,
	std::filesystem::path back
)
{
	std::vector<std::filesystem::path> imagePaths{
		right,
		left,
		top,
		bottom,
		front,
		back
	};

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(false);
	
	for (int i = 0; i < imagePaths.size(); i++) {
		int width, height, nrChannels;
		unsigned char* data = stbi_load(imagePaths[i].string().c_str(), &width, &height, &nrChannels, 4);
		
		std::cout << "Loading cubemap at path " << imagePaths[i] << " (" << width << "x" << height << ") with " << nrChannels << " channels... -\n";

		if (data)
		{
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGBA,
				width,
				height,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				data
			);

			std::cout << "Cubemap cube #" << i+1 <<" at path " << imagePaths[i] << " loaded successfully!- \n";
		}
		else {
			std::cerr << "Failed to load cubemap cube #" << i+1 << "! -\n";
			continue;
		}

		stbi_image_free(data);
	}
}

/// <summary>
/// Releases the OpenGL cubemap texture.
/// </summary>
CubeMap::~CubeMap()
{
	glDeleteTextures(1, &m_id);
}

/// <summary>
/// Activates this cubemap texture for subsequent rendering calls.
/// </summary>
void CubeMap::Use()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
}
