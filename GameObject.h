#pragma once
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GameObject
{
public:
	std::string _name;
	glm::vec3 _position;
	glm::vec3 _forward;
	glm::vec3 _up;

public:
	void static Create(
		const char* name = "", 
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
	void virtual Update(float deltaTime);
	virtual ~GameObject();

protected:
	GameObject(const char* name, glm::vec3 position, glm::vec3 forward, glm::vec3 up);
};

