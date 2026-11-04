#pragma once

#include <filesystem>

/// <summary>
/// Manages an OpenGL texture loaded from an image file.
/// </summary>
class Texture {
public:
	unsigned m_id;
	Texture(std::filesystem::path path);
	~Texture();
	void Use();
};
