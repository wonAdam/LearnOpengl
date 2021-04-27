#include "Game.h"

std::vector<GameObject*> Game::_gameObjects;
Game Game::instance = Game();

Game& Game::Instance()
{
	return instance;
}

void Game::AddGameObejct(GameObject* go)
{
	_gameObjects.push_back(go);
}

void Game::Initialize()
{
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
	for (GameObject* gameObject : _gameObjects)
		delete gameObject;
}
