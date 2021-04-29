#include "Light.h"

#include "Shader.h"
#include "Game.h"
#include "Camera.h"

Light::Light(glm::vec3 diffuse,
    glm::vec3 ambient,
    glm::vec3 specular,
    const char* name,
    glm::vec3 position,
    glm::vec3 forward,
    glm::vec3 up)
    : _diffuse(diffuse), _ambient(ambient), _specular(specular),
    GameObject(name, position, forward, up)
{
}

Light::~Light()
{
}
