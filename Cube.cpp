#include "Cube.h"

#include "Game.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"

void Cube::Update(float deltaTime)
{
    //--- model ---//
    glm::mat4 model = glm::lookAt(_position, _position + _forward, _up);
    _shader->SetMat4("model", model);

    //--- view ---//
    glm::mat4 view = Camera::Instance()->GetViewMatrix();
    _shader->SetMat4("view", view);

    //--- projection ---//
    glm::mat4 proj = glm::perspective(glm::radians(Camera::Instance()->Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
    _shader->SetMat4("proj", proj);

    // Light
    _shader->SetVec3("lightColor", Game::_light->_lightColor);
    _shader->SetVec3("lightPos", Game::_light->_position);

    _shader->Use();
    _texture->Bind();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

Cube::Cube(std::shared_ptr<Shader>& shader, std::shared_ptr<Texture>& texture, 
    const char* name, glm::vec3 position, glm::vec3 forward, glm::vec3 up)
    : GameObject(name, position, forward, up)
{
    // VBO & VAO 
    glGenVertexArrays(1, &VAO);
    GLuint VBO;
    glGenBuffers(1, &VBO);
    // VBO data set
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Bind VAO
    glBindVertexArray(VAO);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // normal vector
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Shader & Texture
    _texture = texture;
    _shader = shader;
    _shader->Use();
    for (std::vector<GLuint>::size_type i = 0; i < texture->textures.size(); i++)
    {
        _shader->SetInt("texture" + std::to_string(i), i);
    }
}

Cube::Cube(std::shared_ptr<Shader>&& shader, std::shared_ptr<Texture>&& texture, const char* name, glm::vec3 position, glm::vec3 forward, glm::vec3 up)
    : Cube(shader, texture, name, position, forward, up)
{
}

Cube::~Cube()
{
}
