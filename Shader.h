#pragma once
#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	GLuint ID;

	Shader(const char* vertexFilePath, const char* fragmentFilePath);
	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, glm::mat4 value) const;

private:
	std::string read_shader(const char* path) const;
	void check_shader_compile_error(GLint shader) const;
	void check_program_link_error(GLint program) const;
};

