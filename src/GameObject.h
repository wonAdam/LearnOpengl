#pragma once
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

// GameObject <Abstract Class>
class GameObject
{
public:
	std::string _name;
	glm::vec3 _position;
	glm::vec3 _forward;
	glm::vec3 _up;

public:
	void virtual Update(float deltaTime) = 0;
	virtual ~GameObject();
protected:
	GameObject(
		const char* name = "", 
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f), 
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
};

