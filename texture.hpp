#pragma once

class Texture {
public:
	unsigned id;
	Texture(const char* path);
	void bind() const;
private:
	//int width;
	//int height;
	//int nrChannels;
	//static void build();
};
