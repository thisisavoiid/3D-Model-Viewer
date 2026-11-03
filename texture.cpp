#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "texture.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

Texture::Texture(const char* path)
{
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 4); 

	std::cout << "Loading texture at path " << path << " (" << width << "x" << height << ") with " << nrChannels << " channels... -\n";

	if (data) {
		GLenum format = GL_RGBA;
		GLenum internalFormat = GL_RGBA;

		switch (nrChannels) {
		case 1:
			format = GL_RED;
			internalFormat = GL_RED;
			break;
		case 2:
			format = GL_RG;
			internalFormat = GL_RG;
			break;
		case 3:
			format = GL_RGB;
			internalFormat = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			internalFormat = GL_RGBA;
			break;
		default:
			std::cerr << "Unsupported number of channels: " << nrChannels << "! -\n";
			stbi_image_free(data);
			return;
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		std::cout << "Texture at path " << path << " loaded successfully! -\n";
	}
	else {
		std::cerr << "Failed to load texture! -\n";
	}
	
	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::Use()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_id);
}
