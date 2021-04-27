#include "Game.h"

Game Game::instance = Game();

Game& Game::Instance()
{
	return instance;
}

void Game::AddGameObejct(GameObject* go)
{
    instance._gameObjects.push_back(go);
}

void Game::Initialize()
{
    glm::vec3 cubePositions[] = {
        glm::vec3(1.0f,  1.0f,  1.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    std::shared_ptr<Shader> shader(new Shader("vertexshader.vert", "fragmentshader.frag"));
    const char* paths[] = {
       "container.jpg",
       "doge.png"
    };
    std::shared_ptr<Texture> texture(new Texture(2, paths));
    for (auto& pos : cubePositions)
        Cube::Create(shader, texture, "", pos);
}

void Game::Update(float deltaTime)
{
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
}
