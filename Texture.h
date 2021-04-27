#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include "stb_image.h"

#define MAX_TEXTURE_NUM 3

class Texture
{
public:
	std::vector<GLuint> textures;
	void Bind();
	Texture(unsigned int num, const char** path);
	Texture(const char* path);
	virtual ~Texture();
private:
	GLuint Generate_Texture(const char* path);
};

