#include "Game.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Gui.h"
#include "GameObject.h"
#include "Shader.h"
#include "Cube.h"
#include "Light.h"
#include "Camera.h"

Game* Game::instance = new Game();
Light* Game::gLight = nullptr;
Camera* Game::gCamera = nullptr;
Gui* Game::gGui = nullptr;

Game* Game::Instance()
{
	return instance;
}

void Game::AddGameObejct(GameObject* go)
{
    instance->_gameObjects.push_back(go);
}

void Game::Initialize()
{
    gGui = new Gui();

    gCamera = new Camera();
    Game::AddGameObejct(gCamera);

    gLight = new Light(glm::vec3(1.0f, 1.0f, 1.0f), 
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        "Light", 
        glm::vec3(5.0f, 0.0f, -5.0f));
    Game::AddGameObejct(gLight);

    std::shared_ptr<Shader> shader(new Shader("src/vertexshader.vert", "src/fragmentshader.frag"));
    shader->SetSampler2D("texture0", "img/container2.png");
    shader->SetSampler2D("texture1", "img/doge.png");
    shader->SetSampler2D("material.specular", "img/container2_specular.png");

    //glm::vec3 cubePositions[] = {
    //    glm::vec3(1.0f,  1.0f,  -5.0f),
    //    glm::vec3(2.0f,  5.0f, -10.0f),
    //    glm::vec3(-1.5f, -2.2f, -10.5f),
    //    glm::vec3(-3.8f, -2.0f, -12.3f),
    //    glm::vec3(2.4f, -0.4f, -5.5f),
    //    glm::vec3(-1.7f,  3.0f, -7.5f),
    //    glm::vec3(1.3f, -2.0f, -8.5f),
    //    glm::vec3(1.5f,  2.0f, -6.5f),
    //    glm::vec3(1.5f,  0.2f, -3.5f),
    //    glm::vec3(-1.3f,  1.0f, -6.5f)
    //};

    //int i = 0;
    //for (auto& pos : cubePositions)
    //{
    //    GameObject* go = new Cube(shader, ("Cube" + std::to_string(i++)).c_str(), pos);
    //    Game::AddGameObejct(go);
    //}

    Cube* c = new Cube(shader, "Cube", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f));
    Game::AddGameObejct(c);
}

void Game::Update(float deltaTime, float gameTime)
{
    float radian = glm::radians(gameTime * 150.0f);
    float r = 5.0f;
    Game::gLight->_position
        = glm::vec3(0.0f, 3.0f, -5.0f) + glm::vec3(r * glm::cos(radian), 0.0f, r * glm::sin(radian));

    Game::gLight->_diffuse.r = sin(gameTime * 2.0f);
    Game::gLight->_diffuse.g = sin(gameTime * 0.5f);
    Game::gLight->_diffuse.b = sin(gameTime * 1.2f);
    Game::gLight->_ambient = glm::vec3(0.1f) * Game::gLight->_diffuse;


    for (GameObject* gameObject : _gameObjects)
    {
        gameObject->Update(deltaTime);
    }

    gGui->Update();
}

Game::Game()
{

}

Game::~Game()
{
	for (auto& gameObject : _gameObjects)
		delete gameObject;

    if (gGui != nullptr)
        delete gGui;
    if (gLight != nullptr)
        delete gLight;
    if (gCamera != nullptr)
        delete gCamera;
}
