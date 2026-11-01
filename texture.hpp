#pragma once

class Texture {
public:
	unsigned id;
	Texture(const char* path);
	void bind();
};
