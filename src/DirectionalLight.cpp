#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(
    glm::vec3 direction,
    glm::vec3 diffuse,
    glm::vec3 ambient,
    glm::vec3 specular,
    const char* name,
    glm::vec3 position,
    glm::vec3 forward,
    glm::vec3 up)
	: _direction(direction), Light(diffuse, ambient, specular, name, position, forward, up)
{
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::Update(float deltaTime)
{
}
