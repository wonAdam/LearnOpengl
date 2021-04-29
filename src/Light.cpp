#include "Light.h"

#include "Shader.h"
#include "Game.h"
#include "Camera.h"

void Light::Update(float deltaTime)
{
    //--- model ---//
    glm::mat4 model = glm::translate(glm::mat4(1.0f), _position);
    model = glm::scale(model, glm::vec3(0.4f));
    _shader->SetMat4("model", model);

    //--- view ---//
    glm::mat4 view = Game::gCamera->GetViewMatrix();
    _shader->SetMat4("view", view);

    //--- projection ---//
    glm::mat4 proj = glm::perspective(glm::radians(Game::gCamera->_zoom), 800.0f / 600.0f, 0.1f, 100.0f);
    _shader->SetMat4("proj", proj);

    _shader->SetVec3("diffuse", _diffuse);

    _shader->Use();
    _shader->BindTexture();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);;
}


Light::Light(glm::vec3 direction,
    glm::vec3 diffuse,
    glm::vec3 ambient,
    glm::vec3 specular,
    const char* name,
    glm::vec3 position,
    glm::vec3 forward,
    glm::vec3 up)
    : _direction(direction), _diffuse(diffuse), _ambient(ambient), _specular(specular),
    Cube(std::shared_ptr<Shader>(
        new Shader("src/lightVertex.vert", 
            "src/lightFragment.frag")),
        name, position, forward, up)
{
    _position = -glm::normalize(direction) * 10.0f;
}

Light::~Light()
{
}
