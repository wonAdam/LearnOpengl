#include "Cube.h"
#include "Game.h"

void Cube::Create(
    const char* name, 
    glm::vec3 position, 
    glm::vec3 forward, 
    glm::vec3 up)
{
	Cube* cube = new Cube(name, position, forward, up);

    // VBO & VAO 
    glGenVertexArrays(1, &cube->VAO);
    GLuint VBO;
    glGenBuffers(1, &VBO);
    // VBO data set
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube->vertices), cube->vertices, GL_STATIC_DRAW);
    // Bind VAO
    glBindVertexArray(cube->VAO);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Shader & Texture
    GLuint texture = GenerateTexture("doge.png");
    cube->_texture = texture;

    cube->_shader.use();
    cube->_shader.setInt("texture1", 0);
    cube->_shader.setInt("texture2", 1);

    // Add GameObject to the Global Game
    Game::AddGameObejct(cube);
}

void Cube::Update(float deltaTime)
{
    //--- model ---//
    glm::mat4 model = glm::lookAt(_position, _position + _forward, _up);
    _shader.setMat4("model", model);

    //--- view ---//
    glm::mat4 view = Camera::Instance().GetViewMatrix();
    _shader.setMat4("view", view);

    //--- projection ---//
    glm::mat4 proj = glm::perspective(glm::radians(Camera::Instance().Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
    _shader.setMat4("proj", proj);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

Cube::Cube(const char* name, glm::vec3 position, glm::vec3 forward, glm::vec3 up)
    : _shader("vertexshader.vert", "fragmentshader.frag"), GameObject(name, position, forward, up)
{
}

Cube::~Cube()
{
}
