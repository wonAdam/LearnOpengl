#pragma once
#include "Cube.h"

class Light : public Cube
{
public:
    glm::vec3 _lightColor;

public:
    void virtual Update(float deltaTime) override;
    Light(glm::vec3 lightColor,
        const char* name = "",
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
	virtual ~Light();
};

