#pragma once
#include "Cube.h"

class Light : public Cube
{
public:
    glm::vec3 _direction;
    glm::vec3 _ambient;
    glm::vec3 _diffuse;
    glm::vec3 _specular;

public:
    void virtual Update(float deltaTime) override;
    Light(glm::vec3 direction,
        glm::vec3 diffuse = glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3 ambient = glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f),
        const char* name = "",
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
	virtual ~Light();
};

