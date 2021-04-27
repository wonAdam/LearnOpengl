#include "Game.h"

#include "GameObject.h"
#include "Texture.h"
#include "Shader.h"
#include "Cube.h"
#include "Light.h"

Game* Game::instance = new Game();
Light* Game::_light;

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
    new Light(glm::vec3(1.0f, 1.0f, 1.0f), "Light", glm::vec3(5.0f, 0.0f, -5.0f));

    std::shared_ptr<Shader> shader(new Shader("vertexshader.vert", "fragmentshader.frag"));
    const char* paths[] = {
       "container.jpg",
       "doge.png"
    };

    std::shared_ptr<Texture> texture(new Texture(2, paths));

    int i = 0;
    for (auto& pos : cubePositions)
        new Cube(shader, texture, ("Cube" + std::to_string(i++)).c_str(), pos);
}

void Game::Update(float deltaTime, float gameTime)
{
    float radian = glm::radians(gameTime * 150.0f);
    float r = 5.0f;
    Game::_light->_position = 
        glm::vec3(0.0f, 3.0f, -5.0f) + 
        glm::vec3(r * glm::cos(radian), 0.0f, r * glm::sin(radian));
	
    
    for (GameObject* gameObject : _gameObjects)
		gameObject->Update(deltaTime);
}

Game::Game()
{
    if (instance != nullptr)
    {

    }
}

Game::~Game()
{
	for (auto& gameObject : _gameObjects)
		delete gameObject;
}
