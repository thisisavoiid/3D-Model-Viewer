#pragma once

#include <filesystem>

class Texture {
public:
	unsigned m_id;
	Texture(std::filesystem::path path);
	~Texture();
	void Use();
};
