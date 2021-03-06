#pragma once
#include <vector>
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
	std::vector<std::pair<std::string, GLuint>> _textures;

	Shader(const char* vertexFilePath, const char* fragmentFilePath);
	void Use() const;
	void BindTexture() const;
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetMat4(const std::string& name, glm::mat4 value) const;
	void SetVec3(const std::string& name, glm::vec3 value) const;
	void SetVec3(const std::string& name, float v1, float v2, float v3) const;
	void SetSampler2D(const std::string& name, const char* path);
	void SetBool(const std::string& name, bool value);

private:
	std::string read_shader(const char* path) const;
	void check_shader_compile_error(GLint shader) const;
	void check_program_link_error(GLint program) const;
	GLuint generate_Texture(const char* path);
};

