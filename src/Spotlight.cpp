#include "Spotlight.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Game.h"
#include "Camera.h"

Spotlight::Spotlight(
    glm::vec3 forward,
    const char* name,
    glm::vec3 position,
	glm::vec3 diffuse, 
	glm::vec3 ambient, 
	glm::vec3 specular, 
	glm::vec3 up)
	: Light(diffuse, ambient, specular, name, position, forward, up)
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
    _shader = std::shared_ptr<Shader>(new Shader("src/lightVertex.vert", "src/lightFragment.frag"));
}

Spotlight::~Spotlight()
{
}

void Spotlight::Update(float deltaTime)
{
    //--- model ---//
    glm::mat4 rotate = glm::lookAt(glm::vec3(0.0f), _forward, _up);
    float worldX = glm::dot(_position, glm::vec3(rotate[0]));
    float worldY = glm::dot(_position, glm::vec3(rotate[1]));
    float worldZ = glm::dot(_position, glm::vec3(rotate[2]));
    glm::mat4 model = glm::translate(rotate, glm::vec3(worldX, worldY, worldZ));
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
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
