#pragma once

class Texture {
public:
	unsigned m_id;
	Texture(const char* path);
	~Texture();
	void Use();
};
