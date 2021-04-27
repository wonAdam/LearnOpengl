#include "Light.h"

#include "Shader.h"
#include "Texture.h"
#include "Game.h"
#include "Camera.h"

void Light::Update(float deltaTime)
{
    //--- model ---//
    glm::mat4 model = glm::translate(glm::mat4(1.0f), _position);
    model = glm::scale(model, glm::vec3(0.4f));
    _shader->SetMat4("model", model);

    //--- view ---//
    glm::mat4 view = Camera::Instance()->GetViewMatrix();
    _shader->SetMat4("view", view);

    //--- projection ---//
    glm::mat4 proj = glm::perspective(glm::radians(Camera::Instance()->Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
    _shader->SetMat4("proj", proj);

    _shader->Use();
    _texture->Bind();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);;
}

Light::Light(glm::vec3 lightColor,
    const char* name,
    glm::vec3 position,
    glm::vec3 forward,
    glm::vec3 up)
    : Cube(std::shared_ptr<Shader>(new Shader("lightVertex.vert", "lightFragment.frag")),
        std::shared_ptr<Texture>(new Texture("default_texture.jpg")),
        name, position, forward, up)
{
    _lightColor = lightColor;
    Game::_light = this;
}

Light::~Light()
{
}
