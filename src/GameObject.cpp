#include "GameObject.h"

GameObject::GameObject(const char* name, glm::vec3 position, glm::vec3 forward, glm::vec3 up)
{
	_name = name;
	_position = position;
	_forward = forward;
	_up = up;
}

const glm::vec3& GameObject::GetPosition() const
{
	return _position;
}

const glm::vec3& GameObject::GetForward() const
{
	return _forward;
}

const glm::vec3& GameObject::GetUp() const
{
	return _up;
}

const std::string& GameObject::GetName() const
{
	return _name;
}

void GameObject::SetPosition(glm::vec3 pos)
{
	_position = pos;
}

void GameObject::SetForward(glm::vec3 forward)
{
	_forward = forward;
}

void GameObject::SetUp(glm::vec3 up)
{
	_up = up;
}

void GameObject::SetName(std::string name)
{
	_name = name;
}


GameObject::~GameObject()
{
}
