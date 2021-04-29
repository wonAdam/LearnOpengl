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

    gLight = new Light(glm::vec3(-5.0f, 0.0f, 5.0f),
        glm::vec3(1.0f, 1.0f, 1.0f), 
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        "Light");

    std::shared_ptr<Shader> shader(new Shader("src/vertexshader.vert", "src/fragmentshader.frag"));
    shader->SetSampler2D("material.texture0", "img/container2.png");
    shader->SetSampler2D("material.texture1", "img/doge.png");
    shader->SetSampler2D("material.specular", "img/container2_specular.png");


    Game::AddGameObejct(new Cube(shader, "Cube1", glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.5, 1.0f, 0.5f)));
    Game::AddGameObejct(new Cube(shader, "Cube2", glm::vec3(-2.0f, 1.5f, -2.0f), glm::vec3(0.5, 1.0f, 0.3f)));
    Game::AddGameObejct(new Cube(shader, "Cube3", glm::vec3(-2.5f, -1.0f, 1.0f), glm::vec3(0.2, 1.0f, 0.5f)));
    Game::AddGameObejct(new Cube(shader, "Cube4", glm::vec3(-2.0f, 1.5f, 1.5f), glm::vec3(0.5, 1.2f, 1.3f)));
    Game::AddGameObejct(new Cube(shader, "Cube5", glm::vec3(-1.5f, 1.5f, -1.5f), glm::vec3(1.5, 1.2f, 0.3f)));
    Game::AddGameObejct(new Cube(shader, "Cube6", glm::vec3(-0.5f, -1.5f, 1.5f), glm::vec3(0.5, 1.2f, 1.3f)));

    Cube* c = new Cube(shader, "Cube", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f));
    Game::AddGameObejct(c);
}

void Game::Update(float deltaTime, float gameTime)
{
    for (GameObject* gameObject : _gameObjects)
    {
        gameObject->Update(deltaTime);
    }
    gCamera->Update(deltaTime);
    gLight->Update(deltaTime);
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
