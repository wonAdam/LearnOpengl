#include "Game.h"

#include "GameObject.h"
#include "Shader.h"
#include "Cube.h"
#include "Light.h"
#include "Camera.h"
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/quaternion.hpp>

Game* Game::instance = new Game();
Light* Game::gLight = nullptr;
Camera* Game::gCamera = nullptr;

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
    gCamera = new Camera();
    //Game::AddGameObejct(gCamera);

    gLight = new Light(glm::vec3(1.0f, 1.0f, 1.0f), 
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        "Light", 
        glm::vec3(5.0f, 0.0f, -5.0f));
    //Game::AddGameObejct(gLight);

    glm::vec3 cubePositions[] = {
        glm::vec3(1.0f,  1.0f,  -5.0f),
        glm::vec3(2.0f,  5.0f, -10.0f),
        glm::vec3(-1.5f, -2.2f, -10.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -5.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -8.5f),
        glm::vec3(1.5f,  2.0f, -6.5f),
        glm::vec3(1.5f,  0.2f, -3.5f),
        glm::vec3(-1.3f,  1.0f, -6.5f)
    };

    std::shared_ptr<Shader> shader(new Shader("src/vertexshader.vert", "src/fragmentshader.frag"));
    shader->SetSampler2D("texture0", "img/container2.png");
    shader->SetSampler2D("texture1", "img/doge.png");
    shader->SetSampler2D("material.specular", "img/container2_specular.png");

    int i = 0;
    for (auto& pos : cubePositions)
    {
        GameObject* go = new Cube(shader, ("Cube" + std::to_string(i++)).c_str(), pos);
        Game::AddGameObejct(go);
    }
}

void Game::Update(float deltaTime, float gameTime)
{
    float radian = glm::radians(gameTime * 150.0f);
    float r = 5.0f;
    Game::gLight->SetPosition(glm::vec3(0.0f, 3.0f, -5.0f) +
        glm::vec3(r * glm::cos(radian), 0.0f, r * glm::sin(radian)));

    Game::gLight->_diffuse.r = sin(gameTime * 2.0f);
    Game::gLight->_diffuse.g = sin(gameTime * 0.5f);
    Game::gLight->_diffuse.b = sin(gameTime * 1.2f);
    Game::gLight->_ambient = glm::vec3(0.1f) * Game::gLight->_diffuse;


    Game::gCamera->Update(deltaTime);
    Game::gLight->Update(deltaTime);
    for (GameObject* gameObject : _gameObjects)
    {
        gameObject->Update(deltaTime);
    }
}

Game::Game()
{

}

Game::~Game()
{
	for (auto& gameObject : _gameObjects)
		delete gameObject;

    if (gLight != nullptr)
        delete gLight;
    if (gCamera != nullptr)
        delete gCamera;
}
