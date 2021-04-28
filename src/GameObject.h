#pragma once
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

// GameObject <Abstract Class>
class GameObject
{
protected:
	std::string _name;
	glm::vec3 _position;
	glm::vec3 _forward;
	glm::vec3 _up;

public:
	const glm::vec3& GetPosition() const;
	const glm::vec3& GetForward() const;
	const glm::vec3& GetUp() const;
	const std::string& GetName() const;
	void SetPosition(glm::vec3 pos);
	void SetForward(glm::vec3 forward);
	void SetUp(glm::vec3 up) ;
	void SetName(std::string name);
	void virtual Update(float deltaTime) = 0;
	virtual ~GameObject();
protected:
	GameObject(
		const char* name = "", 
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f), 
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
};

