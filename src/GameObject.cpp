#include "GameObject.h"

#include "glm/gtx/euler_angles.hpp"

GameObject::GameObject(const char* name, glm::vec3 position, glm::vec3 forward, glm::vec3 up)
{
	_name = name;
	_position = position;
	_forward = forward;
	_up = up;

	glm::mat4 lookAt = glm::lookAt(_position, _position + _forward, _up);
	glm::extractEulerAngleYXZ(lookAt, _eulerY, _eulerX, _eulerZ);
}


GameObject::~GameObject()
{
}
