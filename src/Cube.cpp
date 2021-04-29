#include "Cube.h"

#include "Game.h"
#include "Shader.h"
#include "Camera.h"
#include "Light.h"

void Cube::Update(float deltaTime)
{
    //--- model ---//
    glm::mat4 model = glm::lookAt(glm::vec3(0.0f), _forward, _up);
    float worldX = glm::dot(_position, glm::vec3(model[0]));
    float worldY = glm::dot(_position, glm::vec3(model[1]));
    float worldZ = glm::dot(_position, glm::vec3(model[2]));
    model = glm::translate(model, glm::vec3(worldX, worldY, worldZ));
    _shader->SetMat4("model", model);

    //--- view ---//
    glm::mat4 view = Game::gCamera->GetViewMatrix();
    _shader->SetMat4("view", view);

    //--- projection ---//
    glm::mat4 proj = glm::perspective(glm::radians(Game::gCamera->_zoom), 800.0f / 600.0f, 0.1f, 100.0f);
    _shader->SetMat4("proj", proj);

    // Light
    _shader->SetVec3("light.diffuse", Game::gLight->_diffuse);
    _shader->SetVec3("light.ambient", Game::gLight->_ambient);
    _shader->SetVec3("light.specular", Game::gLight->_specular);
    _shader->SetVec3("light.position", Game::gLight->_position);
    _shader->SetFloat("light.constant", Game::gLight->constant);
    _shader->SetFloat("light.linear", Game::gLight->linear);
    _shader->SetFloat("light.quadratic", Game::gLight->quadratic);
    _shader->SetVec3("viewPos", Game::gCamera->_position);

    // Material
    _shader->SetVec3("material.specular", 0.5f, 0.5f, 0.5f);
    _shader->SetFloat("material.shininess", 16.0f);

    _shader->Use();
    _shader->BindTexture();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

Cube::Cube(std::shared_ptr<Shader>& shader, const char* name, glm::vec3 position, glm::vec3 forward, glm::vec3 up)
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

    // Shader
    _shader = shader;
    
}

Cube::Cube(std::shared_ptr<Shader>&& shader, const char* name, glm::vec3 position, glm::vec3 forward, glm::vec3 up)
    : Cube(shader, name, position, forward, up)
{
}

Cube::~Cube()
{
}
