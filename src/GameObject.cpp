#include "GameObject.h"

GameObject::GameObject(const char* name, glm::vec3 position, glm::vec3 forward, glm::vec3 up)
{
	_name = name;
	_position = position;
	_forward = forward;
	_up = up;
}

GameObject::~GameObject()
{
}
