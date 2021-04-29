#include "Game.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Gui.h"
#include "GameObject.h"
#include "Shader.h"
#include "Cube.h"
#include "Light.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "Spotlight.h"
#include "PointLight.h"

Game* Game::instance = new Game();
DirectionalLight* Game::gLight = nullptr;
Camera* Game::gCamera = nullptr;
Gui* Game::gGui = nullptr;
std::vector<PointLight*> Game::pointLights;
std::vector<Spotlight*> Game::spotLights;

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
    gLight = new DirectionalLight(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.1f, 0.1f, 0.1f));
    Spotlight* sl1 = new Spotlight(glm::vec3(2.0f, 2.0f, 1.3f), "Spotlight1", glm::vec3(-3.0f, -2.0f, -3.0f), glm::vec3(0.8f, 0.1f, 0.0f));
    spotLights.push_back(sl1);
    Spotlight* sl2 = new Spotlight(glm::vec3(-2.0f, 2.0f, -1.3f), "Spotlight2", glm::vec3(3.0f, -2.0f, 1.5f), glm::vec3(0.0f, 0.1f, 0.85f));
    spotLights.push_back(sl2);
    PointLight* pl1 = new PointLight("Pointlight1", glm::vec3(-0.5f, -1.0f, -1.8f), glm::vec3(0.05f, 0.85f, 0.1f));
    pointLights.push_back(pl1);

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
    for (GameObject* go : _gameObjects)
    {
        go->Update(deltaTime);
    }
    for (Spotlight* sl : spotLights)
    {
        sl->Update(deltaTime);
    }
    for (PointLight* pl : pointLights)
    {
        pl->Update(deltaTime);
    }

    gCamera->Update(deltaTime);
    if(gLight != nullptr)
        gLight->Update(deltaTime);
    gGui->Update();
}

void Game::SetLightUniformValues(std::shared_ptr<Shader> shader)
{
    // Directional Light
    if (gLight != nullptr)
    {
        shader->SetBool("hasDirLight", true);
        shader->SetVec3("dirLight.diffuse", Game::gLight->_diffuse);
        shader->SetVec3("dirLight.ambient", Game::gLight->_ambient);
        shader->SetVec3("dirLight.specular", Game::gLight->_specular);
        shader->SetVec3("dirLight.direction", Game::gLight->_direction);
    }
    else {
        shader->SetBool("hasDirLight", false);
    }
    // Point Lights
    shader->SetInt("n_of_point_lights", Game::pointLights.size());
    for (int i = 0; i < Game::pointLights.size(); i++)
    {
        PointLight* pl = Game::pointLights[i];
        shader->SetVec3("pointLights[" + std::to_string(i) + "].diffuse", pl->_diffuse);
        shader->SetVec3("pointLights[" + std::to_string(i) + "].ambient", pl->_ambient);
        shader->SetVec3("pointLights[" + std::to_string(i) + "].specular", pl->_specular);
        shader->SetVec3("pointLights[" + std::to_string(i) + "].position", pl->_position);
        shader->SetFloat("pointLights[" + std::to_string(i) + "].constant", pl->constant);
        shader->SetFloat("pointLights[" + std::to_string(i) + "].linear", pl->linear);
        shader->SetFloat("pointLights[" + std::to_string(i) + "].quadratic", pl->quadratic);
    }
    // Spotlights
    shader->SetInt("n_of_spot_lights", Game::spotLights.size());
    for (int i = 0; i < Game::spotLights.size(); i++)
    {
        Spotlight* sl = Game::spotLights[i];
        shader->SetVec3("spotLights[" + std::to_string(i) + "].diffuse", sl->_diffuse);
        shader->SetVec3("spotLights[" + std::to_string(i) + "].ambient", sl->_ambient);
        shader->SetVec3("spotLights[" + std::to_string(i) + "].specular", sl->_specular);
        shader->SetVec3("spotLights[" + std::to_string(i) + "].position", sl->_position);
        shader->SetVec3("spotLights[" + std::to_string(i) + "].direction", sl->_forward);
        shader->SetFloat("spotLights[" + std::to_string(i) + "].constant", sl->constant);
        shader->SetFloat("spotLights[" + std::to_string(i) + "].linear", sl->linear);
        shader->SetFloat("spotLights[" + std::to_string(i) + "].quadratic", sl->quadratic);
        shader->SetFloat("spotLights[" + std::to_string(i) + "].cutOff", sl->cutOff);
        shader->SetFloat("spotLights[" + std::to_string(i) + "].outerCutOff", sl->outerCutOff);
    }

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

    for (auto& pointLight : pointLights)
        delete pointLight;
    for (auto& spotLight : spotLights)
        delete spotLight;
}
