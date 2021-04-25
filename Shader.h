#pragma once
#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	GLuint ID;

	Shader(const char* vertexFilePath, const char* fragmentFilePath);
	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

private:
	std::string read_shader(const char* path) const;
	void check_shader_compile_error(GLint shader) const;
	void check_program_link_error(GLint program) const;
};

